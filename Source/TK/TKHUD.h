// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TKHUD.generated.h"

UCLASS()
class ATKHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATKHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	void ToggleCrossHair();
private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
	bool IsActivatedCrossHair = true;
};

