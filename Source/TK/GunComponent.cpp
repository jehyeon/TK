// Fill out your copyright notice in the Description page of Project Settings.


#include "GunComponent.h"
#include "MagazineComponent.h"

// Sets default values for this component's properties
UGunComponent::UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));

	if (SM.Succeeded())
	{
		GunMesh = SM.Object;
	}
	
	Magazine = CreateDefaultSubobject<UMagazineComponent>(TEXT("Magazine"));
	// temp
	Magazine->SetMaxAmmoCount(30);
	Magazine->SetCurrentAmmoCount(30);
}


// Called when the game starts
void UGunComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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
}

void UGunComponent::UnEquipMagazine()
{
}

void UGunComponent::SetMesh(USkeletalMesh* Mesh)
{
	GunMesh = Mesh;
}
