// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunComponent.generated.h"

class UMagazineComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TK_API UGunComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMesh* GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UMagazineComponent* Magazine;

public:	
	// Sets default values for this component's properties
	UGunComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	bool Fire();
	bool IsEquippedMagazine() { return bIsEquippedMagazine; }
	void EquipMagazine();
	void UnEquipMagazine();

	void SetMesh(USkeletalMesh* Mesh);
	USkeletalMesh* GetMesh() { return GunMesh; }

	bool bIsEquippedMagazine;
};
