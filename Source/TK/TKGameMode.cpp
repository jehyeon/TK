// Copyright Epic Games, Inc. All Rights Reserved.

#include "TKGameMode.h"
#include "TKHUD.h"
#include "TKCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATKGameMode::ATKGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATKHUD::StaticClass();
}
