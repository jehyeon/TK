// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ChestRigWidth = 6;
	ChestRigHeight = 8;

	PocketSize = 2;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// 인벤토리 사이즈 로드
	CreateInventorySlot();
}

void UInventoryComponent::CreateInventorySlot()
{
}

