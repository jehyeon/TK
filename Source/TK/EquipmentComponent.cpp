// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "GunComponent.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// Weapon 초기화
	Weapons.Add(CreateDefaultSubobject<UGunComponent>(TEXT("PrimaryGun")));
	Weapons.Add(CreateDefaultSubobject<UGunComponent>(TEXT("SecondaryGun")));
	//Weapons.Add(CreateDefaultSubobject<UGunComponent>(TEXT("Pistol")));
	//Weapons[0] = nullptr;
	//Weapons[1] = nullptr;
	//Weapons[2] = nullptr;
	Weapons[0]->SetGun(1);
	Weapons[1]->SetGun(2);

	EquippedWeaponIndex = -1;
}

// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UEquipmentComponent::EquipWeapon(int Index, UGunComponent* Weapon)
{
	// TEMP
	Weapons[Index] = Weapon;
}

void UEquipmentComponent::TakeOnWeapon(int Index)
{
	// 동일한 장비에 take on 하려고 하거나 장착한 weapon이 없는 경우
	if (EquippedWeaponIndex == Index || !IsExistWeapon(Index))
	{
		return;
	}

	EquippedWeaponIndex = Index;
}

void UEquipmentComponent::TakeOffWeapon()
{
	EquippedWeaponIndex = -1;
}

bool UEquipmentComponent::IsTakeWeapon()
{
	return EquippedWeaponIndex != -1;
}

bool UEquipmentComponent::IsTakeWeapon(int Index)
{
	return EquippedWeaponIndex == Index;
}

UGunComponent* UEquipmentComponent::GetEquippedWeapon()
{
	if (EquippedWeaponIndex == -1)
	{
		return nullptr;
	}

	return Weapons[EquippedWeaponIndex];
}

USkeletalMesh* UEquipmentComponent::GetEquippedWeaponMesh()
{
	if (EquippedWeaponIndex == -1)
	{
		return nullptr;
	}

	return Weapons[EquippedWeaponIndex]->GetMesh();
}

bool UEquipmentComponent::IsExistWeapon(int index)
{
	return Weapons[index] != nullptr;
}

