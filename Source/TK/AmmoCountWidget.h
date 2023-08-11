// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoCountWidget.generated.h"

class UTextBlock;

UCLASS()
class TK_API UAmmoCountWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetAmmoText(int current, int max);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UTextBlock* CurrentAmmoCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (BindWidget))
	UTextBlock* MaxAmmoCount;
};
