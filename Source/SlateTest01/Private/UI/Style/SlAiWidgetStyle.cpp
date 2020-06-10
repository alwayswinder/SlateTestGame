// Fill out your copyright notice in the Description page of Project Settings.
#include "SlAiWidgetStyle.h"
#include "SlateBasics.h"
#include "SlateGameResources.h"

TSharedPtr<FSlateStyleSet> SlAiWidgetStyle::SlAiStyleInstance = NULL;

void SlAiWidgetStyle::Initialze()
{
	if (!SlAiStyleInstance.IsValid())
	{
		SlAiStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*SlAiStyleInstance);
	}
}

FName SlAiWidgetStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("SlAiStyle"));
	return StyleSetName;
}

void SlAiWidgetStyle::ShutDown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*SlAiStyleInstance);
	ensure(SlAiStyleInstance.IsUnique());
	SlAiStyleInstance.Reset();
}

const ISlateStyle& SlAiWidgetStyle::Get()
{
	return *SlAiStyleInstance;
}

TSharedRef<FSlateStyleSet> SlAiWidgetStyle::Create()
{
	TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(SlAiWidgetStyle::GetStyleSetName(),
		"/Game/UI/Style", "/Game/UI/Style");
	StyleRef->Set("MenuItemFont", FSlateFontInfo("Roboto-Regular.ttf", 50));
	return StyleRef;
}
