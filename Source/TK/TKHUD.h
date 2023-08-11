// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TKHUD.generated.h"

USTRUCT(BlueprintType)
struct FLine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EndX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EndY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LineThickness;
};

UCLASS()
class ATKHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATKHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

public:
	void ToggleCrossHair();

	void AddDrawLine(const FLine& Line);
	void ClearDrawLine();

private:
	UPROPERTY()
	class UTexture2D* CrosshairTex;

	UPROPERTY()
	bool IsActivatedCrossHair = true;

	UPROPERTY()
	TArray<FLine> Lines;
};

