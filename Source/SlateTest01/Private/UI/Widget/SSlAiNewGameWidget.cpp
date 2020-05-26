// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlAiNewGameWidget.h"
#include "SlateOptMacros.h"
#include "SlAiMenuSlateWidgetStyle.h"
#include "SlAiWidgetStyle.h"
#include "SlAiDataHandle.h"
#include "SBox.h"
#include "STextBlock.h"
#include "SOverlay.h"
#include "SEditabletextBox.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiNewGameWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &SlAiWidgetStyle::Get().GetWidgetStyle<FSlAiMenuSlateStyle>("BPSlAiMenuStyle");
	
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)
			
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
			]
			
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(20.f, 0.f, 0.f, 0.f))
			[
				SNew(STextBlock)
				.Font(MenuStyle->Font_40)
				.Text(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"))
			]

			+SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 0.f, 20.f, 0.f))
			[
				SNew(SBox)
				.WidthOverride(300.f)
				.HeightOverride(600.f)
				[
					SAssignNew(EditTextBox, SEditableTextBox)
					.HintText(NSLOCTEXT("SlAiMenu", "RecordNameHint", "Input Record Name!"))
					.Font(MenuStyle->Font_30)
				]
			]
		]
	];
	
}
bool SSlAiNewGameWidget::AllowEnterGame()
{
	FText InputText = EditTextBox->GetText();
	if (InputText.ToString().IsEmpty())
	{
		return false;
	}
	for (TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList); It; ++It) 
	{
		if ((*It).Equals(InputText.ToString()))
		{
			EditTextBox->SetText(FText::FromString(""));
			EditTextBox->SetHintText(NSLOCTEXT("SlAiMenu", "NameRepeateHint", "Record Name Repeated!"));
			return false;
		}
	}
	SlAiDataHandle::Get()->RecordName = InputText.ToString();

	return true;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
