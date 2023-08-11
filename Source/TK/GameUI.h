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

	void NativeOnInitialized() override;

public:
	void Init();
	void ToggleInventory();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UInventoryWidget* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UAmmoCountWidget* AmmoCount;

private:

};
