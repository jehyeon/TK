// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "GridSlotWidget.h"
#include "InventoryComponent.h"
#include "GameUI.h"

void UInventoryWidget::Init(UGameUI* UI, UInventoryComponent* IC)
{
	InventoryComponent = IC;
	GameUI = UI;
	GridSlot->Init(this, IC);
}

//void UInventoryWidget::ShowGrid()
//{
//	GridSlot->CreateLineSegments();
//}
