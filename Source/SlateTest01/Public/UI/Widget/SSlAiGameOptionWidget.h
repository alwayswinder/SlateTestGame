// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlAiTypes.h"


DECLARE_DELEGATE_OneParam(FChangeCulture, const ECultureTeam)

DECLARE_DELEGATE_TwoParams(FChangeVolume, const float, const float)

class SCheckBox;
class SSlider;
class STextBlock;

/**
 * 
 */
class SLATETEST01_API SSlAiGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameOptionWidget)
	{}

	SLATE_EVENT(FChangeCulture, ChangeCulture)
	SLATE_EVENT(FChangeVolume, ChangeVolume)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
private:
	const struct FSlAiMenuSlateStyle *MenuStyle;
	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> CnCheckBox;

	TSharedPtr<SSlider> MuSlider;
	TSharedPtr<SSlider> SoSlider;

	TSharedPtr<STextBlock> MuTextBlock;
	TSharedPtr<STextBlock> SoTextBlock;


	void StyleInitalize();

private:
	void CnCheckBoxStateChange(ECheckBoxState NewState);
	void EnCheckBoxStateChange(ECheckBoxState NewState);

	void MusicSliderChanged(float Value);
	void SoundSliderChanged(float Value);

	FChangeCulture ChangeCulture;
	FChangeVolume ChangeVolume;
};
