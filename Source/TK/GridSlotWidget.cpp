// Fill out your copyright notice in the Description page of Project Settings.


#include "GridSlotWidget.h"
#include "InventoryComponent.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "InventoryWidget.h"
#include "GameUI.h"

//void UGridSlotWidget::NativeOnInitialized()
//{
//}

//void UGridSlotWidget::NativeConstruct()
//{
//}

void UGridSlotWidget::Init(UInventoryWidget* Inventory, UInventoryComponent* IC)
{
	TileSize = 50.f;
	InventoryWidget = Inventory;
	InventoryComponent = IC;

	Cast<UCanvasPanelSlot>(GridBorder->Slot)->SetSize(FVector2D(
		(float)InventoryComponent->GetChestRigWidth() * TileSize,
		(float)InventoryComponent->GetChestRigHeight() * TileSize));
}

void UGridSlotWidget::CreateLineSegments()
{
	// Disable
	return;

	if (InventoryWidget)
	{

		FGeometry Geometry = GridBorder->GetCachedGeometry();
		FVector2D v = Geometry.GetAbsolutePosition();
		FVector2D s = Geometry.GetAbsoluteSize();

		//UE_LOG(LogTemp, Warning, TEXT("%f %f"), v.X, v.Y);
		//UE_LOG(LogTemp, Warning, TEXT("%f %f"), s.X, s.Y);

		int rows = InventoryComponent->GetChestRigWidth();
		int columns = InventoryComponent->GetChestRigHeight();

		float StartX = v.X;
		float EndX = StartX + rows * TileSize;
		float StartY = v.Y;
		float EndY = StartY + columns * TileSize;

		FColor color = FColor::White;
		float thickness = 1.f;

		for (int row = 0; row <= rows; row++)
		{
			float x = row * TileSize;
			InventoryWidget->GetGameUI()->AddDrawLine(StartX + x, StartY, StartX + x, EndY, color, thickness);
		}

		for (int column = 0; column <= columns; column++)
		{
			float y = column * TileSize;
			InventoryWidget->GetGameUI()->AddDrawLine(StartX, StartY + y, EndX, StartY + y, color, thickness);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid InventoryWidget in GridSlotWidget"));
	}
}
