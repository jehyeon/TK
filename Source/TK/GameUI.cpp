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

void UGameUI::Init()
{
}

void UGameUI::ToggleInventory()
{
	if (!IsActivateInventory)
	{
		Inventory->AddToViewport();
	}
	else
	{
		Inventory->RemoveFromViewport();
	}

	IsActivateInventory = !IsActivateInventory;
}
