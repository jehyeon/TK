// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "TKGameInstance.generated.h"

class UDataTable;

UENUM(BlueprintType)
enum class ItemType : uint8
{
	Gun			UMETA(DisplayName = "Gun"),
	Magazine	UMETA(DisplayName = "Magazine"),
	Ammunition	UMETA(DisplayName = "Ammunition")
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IDForType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WidthSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HeightSize;
};

USTRUCT()
struct FGunData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Damage;
};

UCLASS()
class TK_API UTKGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTKGameInstance();

	virtual void Init() override;

	FItemData* GetItemData(int ID);
	FGunData* GetGunData(int ID);

private:
	UPROPERTY()
	UDataTable* ItemDatas;

	UPROPERTY()
	UDataTable* GunDatas;
};
