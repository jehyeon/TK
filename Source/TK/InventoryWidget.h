// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UGridSlotWidget;
class UInventoryComponent;
class UGameUI;

UCLASS()
class TK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (BindWidget))
	UGridSlotWidget* GridSlot;

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY()
	UGameUI* GameUI;

public:
	void Init(UGameUI* UI, UInventoryComponent* IC);
	//void ShowGrid();

	UGameUI* GetGameUI() const { return GameUI; }
};
