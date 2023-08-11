// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUI.h"
#include "InventoryWidget.h"
#include "AmmoCountWidget.h"
#include "TKCharacter.h"
#include "TKHUD.h"

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
	//Inventory->Init()
}

void UGameUI::Init(ATKCharacter* C, APlayerController* PC)
{
	Character = C;
	PlayerController = PC;
	if (PlayerController)
	{
		HUD = Cast<ATKHUD>(PlayerController->GetHUD());
	}

	Inventory->Init(this, C->GetInventoryComponent());
}

void UGameUI::ToggleInventory()
{
	if (!IsActivateInventory)
	{
		Inventory->AddToViewport();
		Inventory->ShowGrid();
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
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
}

void UGameUI::HideCursor()
{
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;
		PlayerController->bEnableMouseOverEvents = false;
	}
}

void UGameUI::AddDrawLine(float StartX, float StartY, float EndX, float EndY, FColor Color, float LineThickness)
{
	if (HUD)
	{
		FLine Line;
		Line.StartX = StartX;
		Line.StartY = StartY;
		Line.EndX = EndX;
		Line.EndY = EndY;
		Line.Color = Color;
		Line.LineThickness = LineThickness;

		HUD->AddDrawLine(Line);
	}
}

void UGameUI::ClearDrawLine()
{
	if (HUD)
	{
		HUD->ClearDrawLine();
	}
}
