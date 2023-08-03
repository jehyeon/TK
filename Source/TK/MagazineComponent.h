// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MagazineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TK_API UMagazineComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMagazineComponent();

protected:
	virtual void BeginPlay() override;

protected:
	// 초기화 필요 (기본 1)
	int MaxAmmoCount = 1;
	// 초기화 필요 (기본 0)
	int CurrentAmmoCount = 0;

public:
	int GetMaxAmmoCount() { return MaxAmmoCount; }
	int GetCurrentAmmoCount() { return CurrentAmmoCount; }

	void SetMaxAmmoCount(int Value);
	void SetCurrentAmmoCount(int Value);

	bool IsEmptyAmmoCount();

	void Fire();
};
