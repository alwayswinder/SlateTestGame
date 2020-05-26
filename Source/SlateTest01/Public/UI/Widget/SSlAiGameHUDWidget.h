// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"


class SSlAiShortcutWidget;
/**
 * 
 */
class SLATETEST01_API SSlAiGameHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	float GetUIScale()const;
public:
	TSharedPtr<SSlAiShortcutWidget> ShortcutWidget;

private:
	FVector2D GetViewPortSize() const;
	
private:
	TAttribute<float> UIScale;
};
