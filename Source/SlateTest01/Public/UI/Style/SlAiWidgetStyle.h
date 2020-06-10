// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
/**
 * 
 */
class FSlateStyleSet;

class SLATETEST01_API SlAiWidgetStyle
{
public:
	static void Initialze();
	static FName GetStyleSetName();
	static void ShutDown();
	static const ISlateStyle& Get();
private:
	static TSharedRef<FSlateStyleSet> Create();
	static TSharedPtr<FSlateStyleSet> SlAiStyleInstance;
};
