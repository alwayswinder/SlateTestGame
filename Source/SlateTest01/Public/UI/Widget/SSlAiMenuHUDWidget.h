 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLATETEST01_API SSlAiMenuHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
private:
	float GetUIScale() const;
	FVector2D GetViewportSize() const;
//	FReply OnClick();
private:
	const struct FSlAiMenuSlateStyle *MenuStyle;
	TAttribute<float> UIScale;
//	SOverlay::FOverlaySlot* ImageSlot;

	TSharedPtr<class SSlAiMenuWidget> MenuWidget;

};
