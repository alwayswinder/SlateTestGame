// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SUniformGridPanel;

/**
 * 
 */
class SLATETEST01_API SSlAiShortcutWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiShortcutWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	void InitializeContainer();
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)override;


private:
	const struct FSlAiGameStyle* GameStyle;
	
	TSharedPtr<STextBlock> ShortcutInfoTextBlock;
	TSharedPtr<SUniformGridPanel> Gridpanel;
	bool IsInitializeContainer;
};
