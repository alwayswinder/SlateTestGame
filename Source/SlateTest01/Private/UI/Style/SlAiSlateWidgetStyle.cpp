// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiSlateWidgetStyle.h"


FSlAiSlateStyle::FSlAiSlateStyle()
{
}

FSlAiSlateStyle::~FSlAiSlateStyle()
{
}

const FName FSlAiSlateStyle::TypeName(TEXT("FSlAiSlateStyle"));

const FSlAiSlateStyle& FSlAiSlateStyle::GetDefault()
{
	static FSlAiSlateStyle Default;
	return Default;
}

void FSlAiSlateStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

