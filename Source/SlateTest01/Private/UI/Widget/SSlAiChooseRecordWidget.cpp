// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlAiChooseRecordWidget.h"
#include "SlateOptMacros.h"
#include "SlAiMenuSlateWidgetStyle.h"
#include "SlAiWidgetStyle.h"
#include "SlAiDataHandle.h"
#include "SBox.h"
#include "STextBlock.h"
#include "SOverlay.h"
#include "STextComboBox.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiChooseRecordWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &SlAiWidgetStyle::Get().GetWidgetStyle<FSlAiMenuSlateStyle>("BPSlAiMenuStyle");

	for (TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList); It; ++It)
	{
		OptionSource.Add(MakeShareable(new FString(*It)));
	}

	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)

			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(20.f, 0.f, 0.f, 0.f))
			[
				SNew(STextBlock)
				.Font(MenuStyle->Font_40)
				.Text(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"))
			]

			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 0.f, 20.f, 0.f))
			[
				SNew(SBox)
				.WidthOverride(300.f)
				.HeightOverride(600.f)
				[
					SAssignNew(RecordComboBox, STextComboBox)
					.Font(MenuStyle->Font_30)
					.OptionsSource(&OptionSource)
				]
			]
		]
	];
	

	RecordComboBox->SetSelectedItem(OptionSource[0]);
}
void SSlAiChooseRecordWidget::UpdateRecordName()
{
	SlAiDataHandle::Get()->RecordName = *RecordComboBox->GetSelectedItem().Get();

}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
