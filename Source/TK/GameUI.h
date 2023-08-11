// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameUI.generated.h"

class UInventoryWidget;
class UAmmoCountWidget;

UCLASS()
class TK_API UGameUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	//void NativeOnInitialized() override;
	void NativeConstruct() override;

public:
	void SetPlayerController(APlayerController* PlayerController);
	void ToggleInventory();

	void ShowCursor();
	void HideCursor();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UInventoryWidget* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UAmmoCountWidget* AmmoCount;

	UPROPERTY()
	bool IsActivateInventory;

	UPROPERTY()
	APlayerController* PC;

private:

};
