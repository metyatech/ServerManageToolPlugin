// Copyright Epic Games, Inc. All Rights Reserved.

#include "ServerManageLibrary.h"

#include "Engine/Engine.h"
#include "Engine/NetDriver.h"
#include "Engine/World.h"
#include "HAL/PlatformMisc.h"
#include "Misc/App.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "IPAddress.h"

DEFINE_LOG_CATEGORY_STATIC(LogServerManageLibrary, Log, All);

#define LOCTEXT_NAMESPACE "FServerManageLibraryModule"

void FServerManageLibraryModule::StartupModule()
{
	if (!IsRunningDedicatedServer()) {
		return;
	}

	FString ExpectedPortText;
	if (!FParse::Value(FCommandLine::Get(), TEXT("ServerManageExpectedPort="),
	                   ExpectedPortText)) {
		return;
	}

	if (!LexTryParseString(ExpectedServerPort, *ExpectedPortText) ||
	    ExpectedServerPort < 1 || ExpectedServerPort > 65535) {
		UE_LOG(LogServerManageLibrary, Error,
		       TEXT("SMT_PORT_VALIDATION_FAILED expected_port=%s actual_port=unknown world=unknown pid=%u action=request_clean_exit requested_status=2 reason=invalid_expected_port"),
		       *ExpectedPortText, FPlatformProcess::GetCurrentProcessId());
		FPlatformMisc::RequestExitWithStatus(
		    false, 2, TEXT("ServerManageExpectedPort is invalid"));
		return;
	}

	PortValidationTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
	    FTickerDelegate::CreateRaw(
	        this, &FServerManageLibraryModule::ValidateExpectedServerPort),
	    0.1f);
}

void FServerManageLibraryModule::ShutdownModule()
{
	StopPortValidationTicker();
}

bool FServerManageLibraryModule::ValidateExpectedServerPort(float DeltaTime) {
	if (GEngine == nullptr) {
		return true;
	}

	for (const FWorldContext& WorldContext : GEngine->GetWorldContexts()) {
		UWorld* const World = WorldContext.World();
		if (World == nullptr || World->GetNetMode() != NM_DedicatedServer) {
			continue;
		}

		UNetDriver* const NetDriver = World->GetNetDriver();
		if (NetDriver == nullptr) {
			continue;
		}

		const TSharedPtr<const FInternetAddr> LocalAddress =
		    NetDriver->GetLocalAddr();
		if (!LocalAddress.IsValid() || LocalAddress->GetPort() == 0) {
			continue;
		}

		const int32 ActualServerPort = LocalAddress->GetPort();
		const uint32 ProcessId = FPlatformProcess::GetCurrentProcessId();
		StopPortValidationTicker();

		if (ActualServerPort == ExpectedServerPort) {
			UE_LOG(LogServerManageLibrary, Log,
			       TEXT("SMT_PORT_VALIDATION_PASSED expected_port=%d actual_port=%d world=%s pid=%u"),
			       ExpectedServerPort, ActualServerPort, *World->GetName(), ProcessId);
			return false;
		}

		UE_LOG(LogServerManageLibrary, Error,
		       TEXT("SMT_PORT_VALIDATION_FAILED expected_port=%d actual_port=%d world=%s pid=%u action=request_clean_exit requested_status=2 reason=port_mismatch"),
		       ExpectedServerPort, ActualServerPort, *World->GetName(), ProcessId);
		FPlatformMisc::RequestExitWithStatus(
		    false, 2, TEXT("ServerManageExpectedPort does not match bound port"));
		return false;
	}

	return true;
}

void FServerManageLibraryModule::StopPortValidationTicker() {
	if (PortValidationTickerHandle.IsValid()) {
		FTSTicker::RemoveTicker(PortValidationTickerHandle);
		PortValidationTickerHandle.Reset();
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FServerManageLibraryModule, ServerManageLibrary)
