// Fill out your copyright notice in the Description page of Project Settings.


#include "TKGameInstance.h"

UTKGameInstance::UTKGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> ITEM_DATA(TEXT("DataTable'/Game/Data/ItemTable.ItemTable'"));

	if (ITEM_DATA.Succeeded())
	{
		ItemDatas = ITEM_DATA.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> GUN_DATA(TEXT("DataTable'/Game/Data/GunTable.GunTable'"));

	if (GUN_DATA.Succeeded())
	{
		GunDatas = GUN_DATA.Object;
	}
}

void UTKGameInstance::Init()
{
	Super::Init();
}

FItemData* UTKGameInstance::GetItemData(int ID)
{
	return ItemDatas->FindRow<FItemData>(*FString::FromInt(ID), TEXT(""));
}

FGunData* UTKGameInstance::GetGunData(int ID)
{
	return GunDatas->FindRow<FGunData>(*FString::FromInt(ID), TEXT(""));
}
