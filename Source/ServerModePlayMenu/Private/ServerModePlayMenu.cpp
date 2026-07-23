// Copyright Epic Games, Inc. All Rights Reserved.

#include "ServerModePlayMenu.h"

#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Notifications/NotificationManager.h"
#include "IPAddress.h"
#include "Misc/App.h"
#include "ServerInfoSettings.h"
#include "ServerModeSetting.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "ToolMenus.h"
#include "Widgets/Notifications/SNotificationList.h"

DEFINE_LOG_CATEGORY_STATIC(LogServerModePlayMenu, Log, All);

static const FName ServerModePlayMenuTabName("ServerModePlayMenu");

#define LOCTEXT_NAMESPACE "FServerModePlayMenuModule"

class FInternalServerModeCommandCallbacks {
public:
	static int32 GetServerPlayMode();
	static void  SetServerPlayMode(int32 Value);
};

namespace {

bool CanBindUdpPort(const int32 Port) {
	ISocketSubsystem* const SocketSubsystem =
	    ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (SocketSubsystem == nullptr) {
		return false;
	}

	FUniqueSocket Socket = SocketSubsystem->CreateUniqueSocket(
	    NAME_DGram, TEXT("ServerModePlayMenuPortPreflight"), true);
	if (!Socket.IsValid()) {
		return false;
	}

	const TSharedRef<FInternetAddr> Address = SocketSubsystem->CreateInternetAddr();
	Address->SetAnyAddress();
	Address->SetPort(Port);

	return Socket->SetReuseAddr(false) && Socket->Bind(*Address);
}

FString FormatPorts(const TArray<int32>& Ports) {
	FString Result;
	for (int32 Index = 0; Index < Ports.Num(); ++Index) {
		if (Index > 0) {
			Result += TEXT(",");
		}
		Result += FString::FromInt(Ports[Index]);
	}
	return Result;
}

}

void FServerModePlayMenuModule::StartupModule() {
	UToolMenus::RegisterStartupCallback(
	    FSimpleMulticastDelegate::FDelegate::CreateRaw(
	        this, &FServerModePlayMenuModule::RegisterMenus));

	FEditorDelegates::BeginPIE.AddRaw(this,
	                                  &FServerModePlayMenuModule::OnBeginPIE);
	FEditorDelegates::EndPIE.AddRaw(this, &FServerModePlayMenuModule::OnEndPIE);

	RegisterSeverInfoSetting();
}

void FServerModePlayMenuModule::ShutdownModule() {
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	UnregisterSeverInfoSetting();
}

void FServerModePlayMenuModule::RegisterMenus() {
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* PlayMenu =
	    UToolMenus::Get()->ExtendMenu("UnrealEd.PlayWorldCommands.PlayMenu");
	{
		FToolMenuSection& Section =
		    PlayMenu->FindOrAddSection("LevelEditorPlayInWindowNetwork");
		{
			Section.AddSubMenu(
			    "ServerMode", LOCTEXT("ServerModeMenu", "Server Mode"),
			    LOCTEXT("ServerModeToolTip", "The type of the server to connect to."),
			    FNewMenuDelegate::CreateLambda([](FMenuBuilder& InMenuBuilder) {
				    const UEnum* ServerPlayModeEnum = FindObject<UEnum>(
				        nullptr, TEXT("/Script/ServerModePlayMenu.EServerPlayMode"));

				    const auto NumPlayModes = ServerPlayModeEnum->NumEnums();
				    for (auto i = decltype(NumPlayModes){0}; i < NumPlayModes - 1;
				         ++i) {
					    FUIAction Action(
					        FExecuteAction::CreateStatic(
					            &FInternalServerModeCommandCallbacks::SetServerPlayMode,
					            i),
					        FCanExecuteAction(),
					        FIsActionChecked::CreateLambda(
					            [](int32 Index) {
						            return FInternalServerModeCommandCallbacks::
						                       GetServerPlayMode() == Index;
					            },
					            i));

					    InMenuBuilder.AddMenuEntry(
					        ServerPlayModeEnum->GetDisplayNameTextByIndex(i),
					        ServerPlayModeEnum->GetToolTipTextByIndex(i), FSlateIcon(),
					        Action, NAME_None, EUserInterfaceActionType::RadioButton);
				    }
			    }),
			    false);
		}
	}
}

void FServerModePlayMenuModule::OnBeginPIE(const bool bIsSimulating) {
	if (SERVER_LocalLaunch ==
	    FInternalServerModeCommandCallbacks::GetServerPlayMode()) {
		const auto* const ServerInfoConfig = GetDefault<UServerInfoSettings>();
		const auto&       ServerList       = ServerInfoConfig->ServerList;
		const auto&       NumServerList    = ServerList.Num();

		ensureAlways(ServerProcesses.empty());

		TArray<int32> UnavailablePorts;
		UnavailablePorts.Reserve(NumServerList);
		for (int32 Index = 0; Index < NumServerList; ++Index) {
			const int32 Port = 7777 + Index;
			if (!CanBindUdpPort(Port)) {
				UnavailablePorts.Add(Port);
			}
		}

		if (UnavailablePorts.Num() > 0) {
			UE_LOG(LogServerModePlayMenu, Error,
			       TEXT("SMT_PORT_PREFLIGHT_FAILED unavailable_ports=%s server_count=%d started_server_count=0 rollback_count=0"),
			       *FormatPorts(UnavailablePorts), NumServerList);
			ShowPortConflictNotification(UnavailablePorts);
			return;
		}

		UE_LOG(LogServerModePlayMenu, Log,
		       TEXT("SMT_PORT_PREFLIGHT_PASSED first_port=%d last_port=%d server_count=%d"),
		       7777, 7777 + NumServerList - 1, NumServerList);

		ServerProcesses.reserve(NumServerList);

		int32 Port = 7777;
		for (const auto& ServerMap : ServerList) {
			auto ServerProcessPtr =
			    std::make_shared<ServerProcess>(ServerMap.MapName, Port);
			if (!ServerProcessPtr->IsValid()) {
				UE_LOG(LogServerModePlayMenu, Error,
				       TEXT("SMT_SERVER_PROCESS_LAUNCH_FAILED map=%s requested_port=%d rollback_count=%d final_managed_server_count=0"),
				       *ServerMap.MapName, Port, static_cast<int32>(ServerProcesses.size()));
				ServerProcesses.clear();
				return;
			}
			ServerProcesses.push_back(MoveTemp(ServerProcessPtr));
			++Port;
		}
	}
}

void FServerModePlayMenuModule::ShowPortConflictNotification(
	const TArray<int32>& UnavailablePorts) {
	if (!FSlateApplication::IsInitialized() || FApp::IsUnattended()) {
		return;
	}

	FNotificationInfo Notification(FText::FromString(
	    FString::Printf(TEXT("Local Launch stopped: UDP port conflict on %s."),
	                    *FormatPorts(UnavailablePorts))));
	Notification.ExpireDuration = 8.0f;
	FSlateNotificationManager::Get().AddNotification(Notification);
}

void FServerModePlayMenuModule::OnEndPIE(const bool bIsSimulating) {
	ServerProcesses.clear();
}

void FServerModePlayMenuModule::RegisterSeverInfoSetting() {
	if (ISettingsModule* SettingsModule =
	        FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings(
		    "Project", "Project", "ServerInfoSettings",
		    LOCTEXT("ServerInfoSettingName", "Servers"),
		    LOCTEXT("ServerInfoDescription", "Settings about servers"),
		    GetMutableDefault<UServerInfoSettings>());
	}
}

void FServerModePlayMenuModule::UnregisterSeverInfoSetting() {
	if (ISettingsModule* SettingsModule =
	        FModuleManager::GetModulePtr<ISettingsModule>("Settings")) {
		SettingsModule->UnregisterSettings("Project", "Project",
		                                   "ServerInfoSettings");
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FServerModePlayMenuModule, ServerModePlayMenu)

int32 FInternalServerModeCommandCallbacks::GetServerPlayMode() {
	const auto* const ServerModeSetting = GetDefault<UServerModeSetting>();
	return static_cast<int32>(ServerModeSetting->GetServerPlayMode());
}
void FInternalServerModeCommandCallbacks::SetServerPlayMode(const int32 Value) {
	auto* const ServerModeSetting = GetMutableDefault<UServerModeSetting>();
	ServerModeSetting->SetServerPlayMode(static_cast<EServerPlayMode>(Value));

	ServerModeSetting->PostEditChange();
	ServerModeSetting->SaveConfig();
}
