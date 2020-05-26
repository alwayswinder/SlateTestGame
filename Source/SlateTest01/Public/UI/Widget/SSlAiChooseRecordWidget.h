// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "SlAiTypes.h"

/**
 * 
 */
class STextComboBox;

class SLATETEST01_API SSlAiChooseRecordWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiChooseRecordWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void UpdateRecordName();

private:
	const struct FSlAiMenuSlateStyle *MenuStyle;
	TSharedPtr<STextComboBox> RecordComboBox;

	TArray<TSharedPtr<FString>> OptionSource;
};
