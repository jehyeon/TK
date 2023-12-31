// Copyright Epic Games, Inc. All Rights Reserved.

#include "TKHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

ATKHUD::ATKHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}

void ATKHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair
	if (IsActivatedCrossHair)
	{
		// find center of the Canvas
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

		// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
		const FVector2D CrosshairDrawPosition((Center.X),
			(Center.Y + 20.0f));

		// draw the crosshair
		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}

	// Line 그리기
	if (Lines.Num() > 0)
	{
		for (const FLine& Line : Lines)
		{
			DrawLine(Line.StartX, Line.StartY, Line.EndX, Line.EndY,
					 Line.Color, Line.LineThickness);
		}
	}
}

void ATKHUD::ToggleCrossHair()
{
	IsActivatedCrossHair = !IsActivatedCrossHair;
}

void ATKHUD::AddDrawLine(const FLine& Line)
{
	Lines.Add(Line);
}

void ATKHUD::ClearDrawLine()
{
	Lines.Empty();
}
