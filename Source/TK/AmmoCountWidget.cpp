// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCountWidget.h"
#include "Components/TextBlock.h"

void UAmmoCountWidget::SetAmmoText(int current, int max)
{
	CurrentAmmoCount->SetText(FText::FromName(FName(TEXT("%d"), current)));
	MaxAmmoCount->SetText(FText::FromName(FName(TEXT("/ %d"), max)));
}
