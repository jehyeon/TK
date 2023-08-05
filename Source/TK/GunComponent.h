// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunComponent.generated.h"

class UMagazineComponent;
class UGunStatComponent;

struct FConstructorStatics
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> AR4;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> Ka47;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> KA74U;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> KA_Val;
	ConstructorHelpers::FObjectFinder<USkeletalMesh> SMG11;
	FConstructorStatics()
		: AR4(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"))
		, Ka47(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47/SK_KA47.SK_KA47'"))
		, KA74U(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/KA74U/SK_KA74U_Y.SK_KA74U_Y'"))
		, KA_Val(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/KA_Val/SK_KA_Val_Y.SK_KA_Val_Y'"))
		, SMG11(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/SMG11/SK_SMG11_Nostock_Y.SK_SMG11_Nostock_Y'"))
	{}
};

DECLARE_DELEGATE_OneParam(FInputTakeWeaponDelegate, const int);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TK_API UGunComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMesh* GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UMagazineComponent* Magazine;

	UPROPERTY(VisibleDefaultsOnly, Category = Stat)
	UGunStatComponent* Stat;

public:	
	// Sets default values for this component's properties
	UGunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	bool IsExist() { return bIsExist; }
	void OnFire();
	bool Fire();
	bool IsEquippedMagazine() { return bIsEquippedMagazine; }
	void EquipMagazine();
	void UnequipMagazine();

	void SetGun(int GunID);
	USkeletalMesh* GetMesh() { return GunMesh; }
	UMagazineComponent* GetMagazine() { return Magazine; }
	UGunStatComponent* GetStat() { return Stat; }

private:
	bool bIsEquippedMagazine;
	bool bIsExist;
};
