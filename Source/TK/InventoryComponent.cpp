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
	for (int i = 0; i < ChestRigHeight * ChestRigWidth; i++)
	{
		ChestRig.Add(nullptr);
	}
}

bool UInventoryComponent::TryAddItem(UItem* Item)
{
	FIntPoint Size = Item->GetItemSize();
	int Width = Size.X;
	int Height = Size.Y;

	if (Width == 0 || Height == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Item Size in InventoryComp::TryAddItem"));
		return;
	}

	for (int i = 0; i < ChestRigHeight * ChestRigWidth; i++)
	{
		// 빈 슬롯인 경우
		if (!ChestRig[i])
		{
			if (IsAvaliableRoom(i, Width, Height))
			{
				AddItemAt(Item, i);

				return true;
			}
		}
	}

	// Temp, ChestRig에 빈자리가 없음
	//		다른 슬롯 확인 로직 추가 예정
	return false;
}


bool UInventoryComponent::IsValidIndex(TArray<UItem*> Array, int Index)
{
	if (Index < 0 || Index >= Array.Num())
	{
		return true;
	}

	return false;
}

bool UInventoryComponent::IsValidTile(FIntPoint Point)
{
	return IsValidTile(Point.X, Point.Y);
}

bool UInventoryComponent::IsValidTile(int X, int Y)
{
	// TEMP: ChestRig만 검사, 수정 예정
	if (X < 0 || X >= ChestRigWidth || Y < 0 || Y >= ChestRigHeight)
	{
		return false;
	}

	return true;
}

UItem* UInventoryComponent::GetItemUsingTilePosition(int X, int Y)
{
	if (!IsValidTile(X, Y))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Pos in InventoryComp::GetItemUsingTilePosition"));
		return nullptr;
	}

	int Index = Y * ChestRigWidth + X;

	return ChestRig[Index];
}

FIntPoint UInventoryComponent::ConvertIndexToTilePosition(int Index)
{

	if (!IsValidIndex(ChestRig, Index))
	{
		return FIntPoint(-1, -1);
	}

	int y = Index / ChestRigWidth;
	int x = Index % ChestRigWidth;

	return FIntPoint(x, y);
}

bool UInventoryComponent::IsAvaliableRoom(int LeftTopIndex, int WidthSize, int HeightSize)
{
	FIntPoint LeftTopPos = ConvertIndexToTilePosition(LeftTopIndex);
	if (!IsValidTile(LeftTopPos))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Index in InventoryComp::IsAvaliableRoom"));
		return;
	}

	for (int j = 0; j < HeightSize; j++)
	{
		for (int k = 0; k < WidthSize; k++)
		{
			// 슬롯에 아이템이 있는 경우
			if (GetItemUsingTilePosition(LeftTopPos.X + k, LeftTopPos.Y + j) != nullptr)
			{
				// TEMP: 잘못된 position이어도 nullptr이므로 수정 필요
				return false;
			}
		}
	}

	return true;
}

void UInventoryComponent::AddItemAt(UItem* Item, int TopLeftIndex)
{
	// Temp: ChestRig 고정, 추후 수정 예정
	ChestRig[TopLeftIndex] = Item;
}
