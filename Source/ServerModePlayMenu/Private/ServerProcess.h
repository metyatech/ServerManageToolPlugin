// Copyright 2024-2026 metyatech. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class ServerProcess {
public:
	ServerProcess(const FString& MapName, int32 Port = 7777);

public:
	void Kill();
	bool IsValid() const;
	int32 GetRequestedPort() const;

public:
	~ServerProcess();

private:
	FProcHandle ProcessHandle;
	int32 RequestedPort = 0;
};
