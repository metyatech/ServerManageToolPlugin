// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Containers/Ticker.h"
#include "Modules/ModuleManager.h"

class FServerManageLibraryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	bool ValidateExpectedServerPort(float DeltaTime);
	void StopPortValidationTicker();

	int32 ExpectedServerPort = 0;
	FTSTicker::FDelegateHandle PortValidationTickerHandle;
};
