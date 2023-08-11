// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class ItemType : uint8
{
	None		UMETA(DisplayName = "None"),
	Gun			UMETA(DisplayName = "Gun"),
	Magazine	UMETA(DisplayName = "Magazine"),
	Ammunition	UMETA(DisplayName = "Ammunition")
};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemData()
		: Name(TEXT("")), Type(ItemType::None), MaxCount(0), WidthSize(0), HeightSize(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ItemType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WidthSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HeightSize;
};

UCLASS()
class TK_API UItem : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	int ID;

	UPROPERTY()
	FItemData Data;

	UPROPERTY()
	UTexture2D* Texture;

public:
	FIntPoint& GetItemSize() const;
};
