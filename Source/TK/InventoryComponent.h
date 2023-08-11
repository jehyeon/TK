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

private:
	// Chest rig
	UPROPERTY()
	int ChestRigWidthSize;

	UPROPERTY()
	int ChestRigHeightSize;

	UPROPERTY()
	TArray<UItem*> ChestRig;

	// Pocket
	UPROPERTY()
	int PocketSize;

	UPROPERTY()
	TArray<UItem*> Pocket;
};
