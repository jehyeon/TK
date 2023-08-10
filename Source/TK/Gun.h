// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Gun.generated.h"

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
class TK_API UGun : public UItem
{
	GENERATED_BODY()
	
protected:

};
