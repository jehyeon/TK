// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GridSlotWidget.generated.h"

class UInventoryComponent;
class UCanvasPanel;
class UBorder;
class UInventoryWidget;

UCLASS()
class TK_API UGridSlotWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (BindWidget))
	UCanvasPanel* GridCanvasPanel;

	UPROPERTY()
	UInventoryComponent* InventoryComponent;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

protected:
	//void NativeOnInitialized() override;
	//void NativeConstruct() override;

public:
	void Init(UInventoryWidget* Inventory, UInventoryComponent* IC);
	void SetTileSize();
	void CreateLineSegments();

private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	float TileSize;
};
