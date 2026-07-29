// Copyright 2024-2026 metyatech. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FServerInfoSettingsModuleModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
