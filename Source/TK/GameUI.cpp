// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUI.h"
#include "InventoryWidget.h"
#include "AmmoCountWidget.h"

//void UGameUI::NativeOnInitialized()
//{
//	Super::NativeOnInitialized();
//
//
//	IsActivateInventory = false;
//	Inventory->RemoveFromViewport();
//}

void UGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	IsActivateInventory = false;
	Inventory->RemoveFromViewport();
}

void UGameUI::SetPlayerController(APlayerController* PlayerController)
{
	PC = PlayerController;
}

void UGameUI::ToggleInventory()
{
	if (!IsActivateInventory)
	{
		Inventory->AddToViewport();
		ShowCursor();
	}
	else
	{
		Inventory->RemoveFromViewport();
		HideCursor();
	}

	IsActivateInventory = !IsActivateInventory;
}

void UGameUI::ShowCursor()
{
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void UGameUI::HideCursor()
{
	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
	}
}
