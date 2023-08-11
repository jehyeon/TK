// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void CreateInventorySlot();

	int GetChestRigWidth() const { return ChestRigWidth; }
	int GetChestRigHeight() const { return ChestRigHeight; }

	// 아이템 추가 시도
	bool TryAddItem(UItem* Item);

private:
	// Index, Position valid 검증
	bool IsValidIndex(TArray<UItem*> Array, int Index);
	bool IsValidTile(FIntPoint Point);
	bool IsValidTile(int X, int Y);

	// Index to Pos, Pos to Index
	UItem* GetItemUsingTilePosition(int X, int Y);
	FIntPoint ConvertIndexToTilePosition(int Index);

	// LeftTopIndex 기준으로 아이템 크기만큼의 공간이 있는지 확인
	bool IsAvaliableRoom(int LeftTopIndex, int WidthSize, int HeightSize);

	// 아이템 추가 (only by TryAddItem)
	void AddItemAt(UItem* Item, int TopLeftIndex);

private:
	// Chest rig
	UPROPERTY()
	int ChestRigWidth;

	UPROPERTY()
	int ChestRigHeight;

	UPROPERTY()
	TArray<UItem*> ChestRig;

	// Pocket
	UPROPERTY()
	int PocketSize;

	UPROPERTY()
	TArray<UItem*> Pocket;
};
