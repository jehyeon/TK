// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

FIntPoint& UItem::GetItemSize() const
{
	return FIntPoint(Data.WidthSize, Data.HeightSize);
}
