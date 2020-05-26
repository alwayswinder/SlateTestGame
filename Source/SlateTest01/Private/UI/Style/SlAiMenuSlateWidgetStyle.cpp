// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuSlateWidgetStyle.h"


FSlAiMenuSlateStyle::FSlAiMenuSlateStyle()
{
}

FSlAiMenuSlateStyle::~FSlAiMenuSlateStyle()
{
}

const FName FSlAiMenuSlateStyle::TypeName(TEXT("FSlAiMenuSlateStyle"));

const FSlAiMenuSlateStyle& FSlAiMenuSlateStyle::GetDefault()
{
	static FSlAiMenuSlateStyle Default;
	return Default;
}

void FSlAiMenuSlateStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

