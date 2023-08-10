// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TKGameInstance.generated.h"

class UDataTable;
class Item;

UCLASS()
class TK_API UTKGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTKGameInstance();

	virtual void Init() override;

	//FItemData* GetItemData(int ID);
	//FGunData* GetGunData(int ID);

	Item* GetItem(int ID);

private:
	//UPROPERTY()
	//UDataTable* ItemDatas;

	//UPROPERTY()
	//UDataTable* GunDatas;
};
