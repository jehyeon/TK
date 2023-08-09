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
	Weapons[0] = nullptr;
	Weapons[1] = nullptr;
	EquippedWeaponIndex = -1;
}

void UEquipmentComponent::EquipWeapon(int index, UGunComponent* Weapon)
{
	Weapons[index] = Weapon;
}

// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

