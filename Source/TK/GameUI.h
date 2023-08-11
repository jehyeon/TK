// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUI.generated.h"

class UInventoryWidget;
class UAmmoCountWidget;
class ATKCharacter;
class ATKHUD;

UCLASS()
class TK_API UGameUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (BindWidget))
	UInventoryWidget* Inventory;

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (BindWidget))
	UAmmoCountWidget* AmmoCount;

	UPROPERTY()
	ATKCharacter* Character;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	ATKHUD* HUD;

protected:
	//void NativeOnInitialized() override;
	void NativeConstruct() override;

public:
	void Init(ATKCharacter* C, APlayerController* PC);
	void ToggleInventory();

	void ShowCursor();
	void HideCursor();

	void AddDrawLine(float StartX, float StartY, float EndX, float EndY, FColor Color, float LineThickness);
	void ClearDrawLine();

public:

	UPROPERTY()
	bool IsActivateInventory;


private:

};
