// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlAiTypes.h"

/**
 * 
 */
class SEditableTextBox;

class SLATETEST01_API SSlAiNewGameWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiNewGameWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	bool AllowEnterGame();

private:
	const struct FSlAiMenuSlateStyle *MenuStyle;

	TSharedPtr<SEditableTextBox> EditTextBox;
	
};
