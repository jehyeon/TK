// Fill out your copyright notice in the Description page of Project Settings.


#include "GunComponent.h"
#include "GunStatComponent.h"
#include "MagazineComponent.h"

// Sets default values for this component's properties
UGunComponent::UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	
	
	Magazine = CreateDefaultSubobject<UMagazineComponent>(TEXT("Magazine"));
	// temp
	Magazine->SetMaxAmmoCount(30);
	Magazine->SetCurrentAmmoCount(30);

	Stat = CreateDefaultSubobject<UGunStatComponent>(TEXT("Stat"));

	bIsEquippedMagazine = false;
	bIsExist = false;
}

// Called when the game starts
void UGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UGunComponent::OnFire()
{
}

bool UGunComponent::Fire()
{
	if (!Magazine->IsEmptyAmmoCount())
	{
		Magazine->Fire();

		return true;
	}

	return false;
}

void UGunComponent::EquipMagazine()
{
	// temp
	Magazine->SetCurrentAmmoCount(30);
	bIsEquippedMagazine = true;
}

void UGunComponent::UnequipMagazine()
{
	bIsEquippedMagazine = false;
}

void UGunComponent::SetGun(int GunID)
{
	bIsExist = true;
	// temp
	static FConstructorStatics ConstructorStatics;

	switch (GunID)
	{
		case 1:
		{
			GunMesh = ConstructorStatics.AR4.Object;
			break;
		}
		case 2:
		{
			GunMesh = ConstructorStatics.Ka47.Object;
			break;
		}
		case 3:
		{
			GunMesh = ConstructorStatics.KA74U.Object;
			break;
		}
		case 4:
		{
			GunMesh = ConstructorStatics.KA_Val.Object;
			break;
		}
		case 5:
		{
			GunMesh = ConstructorStatics.SMG11.Object;
			break;
		}
	}
	
	Stat->SetGunStat(GunID);
}
