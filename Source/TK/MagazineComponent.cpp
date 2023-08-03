// Fill out your copyright notice in the Description page of Project Settings.


#include "MagazineComponent.h"

// Sets default values for this component's properties
UMagazineComponent::UMagazineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMagazineComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMagazineComponent::SetMaxAmmoCount(int Value)
{
	MaxAmmoCount = Value;
}

void UMagazineComponent::SetCurrentAmmoCount(int Value)
{
	CurrentAmmoCount = Value;
}

bool UMagazineComponent::IsEmptyAmmoCount()
{
	return CurrentAmmoCount < 1;
}

void UMagazineComponent::Fire()
{
	CurrentAmmoCount--;
}

