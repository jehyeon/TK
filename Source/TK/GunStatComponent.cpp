// Fill out your copyright notice in the Description page of Project Settings.


#include "GunStatComponent.h"
#include "TKGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UGunStatComponent::UGunStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}


// Called when the game starts
void UGunStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UGunStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UGunStatComponent::SetGunStat(int GunID)
{
	auto TKGameInstance = Cast<UTKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (TKGameInstance)
	{
		auto GunStat = TKGameInstance->GetGunData(GunID);
		RateOfFire = GunStat->RateOfFire;
		Damage = GunStat->Damage;
	}
}
