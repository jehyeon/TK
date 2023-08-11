// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TKGameMode.generated.h"

class UGameUI;

UCLASS(minimalapi)
class ATKGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATKGameMode();

public:
	UGameUI* GetGameUI();

public:
	UPROPERTY()
	TSubclassOf<UUserWidget> HUD_Class;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	UPROPERTY()
	UGameUI* GameUI;
};



