// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

class UGunComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TK_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	TArray<UGunComponent*> Weapons;

	// Pistol

	// Armor
	// Helmet
	// Chest

	// Bag
	// Bag
	// Chest rig

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void EquipWeapon(int Index, UGunComponent* Weapon);
	void TakeOnWeapon(int Index);
	void TakeOffWeapon();
	bool IsTakeWeapon();
	bool IsTakeWeapon(int Index);
	bool IsExistWeapon(int Index);

	UGunComponent* GetEquippedWeapon();
	USkeletalMesh* GetEquippedWeaponMesh();

private:
	int EquippedWeaponIndex;
};
