// Copyright Epic Games, Inc. All Rights Reserved.

#include "TKGameMode.h"
#include "TKHUD.h"
#include "TKCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameUI.h"

ATKGameMode::ATKGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("Blueprint'/Game/Character/BP_ArmCharacter.BP_ArmCharacter_C'"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATKHUD::StaticClass();

	static ConstructorHelpers::FClassFinder<UGameUI> GAME_UI(TEXT("WidgetBlueprint'/Game/UI/WBP_GameUI.WBP_GameUI_C'"));
	if (GAME_UI.Succeeded())
	{
		HUD_Class = GAME_UI.Class;

		CurrentWidget = CreateWidget(GetWorld(), HUD_Class);
		if (CurrentWidget)
		{
			GameUI = Cast<UGameUI>(CurrentWidget);

			CurrentWidget->AddToViewport();
		}
	}
}

UGameUI* ATKGameMode::GetGameUI()
{
	if (GameUI)
	{
		return GameUI;
	}

	return nullptr;
}
