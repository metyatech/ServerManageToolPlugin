// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ServerInfoSettings.generated.h"

USTRUCT(BlueprintType)
struct SERVERINFOSETTINGSMODULE_API FServerMap {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Server Management")
	FString MapName;

	UPROPERTY(Config, EditAnywhere, Category = "Server Management")
	FString ServerAddress;
};

/**
 *
 */
UCLASS(config = Engine, defaultconfig)
class SERVERINFOSETTINGSMODULE_API UServerInfoSettings: public UObject {
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnyWhere, Category = "Server Management")
	TArray<FServerMap> ServerList;
};
