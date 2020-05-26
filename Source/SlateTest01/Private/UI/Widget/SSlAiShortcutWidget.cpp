// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlAiShortcutWidget.h"
#include "SlateOptMacros.h"
#include "SlAiGameWidgetStyle.h"
#include "SlAiWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiShortcutWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &SlAiWidgetStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");

	IsInitializeContainer = false;


	ChildSlot
		[
			SNew(SBox)
			.WidthOverride(900.f)
			.HeightOverride(160.f)
			[
				SNew(SOverlay)

				+SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				[
					SAssignNew(ShortcutInfoTextBlock, STextBlock)
					.Font(GameStyle->Font_40)
					.ColorAndOpacity(GameStyle->FontColor_White)
				]

				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(0.f, 60.f, 0.f, 0.f))
				[
					SAssignNew(Gridpanel, SUniformGridPanel)
				]
			]
		];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiShortcutWidget::InitializeContainer()
{
	for (int i=0; i<9; ++i)
	{
		TSharedPtr<SBorder> ContainerBorder;
		TSharedPtr<SBorder> ObjectImage;
		TSharedPtr<STextBlock> ObjectNumText;

		SAssignNew(ContainerBorder, SBorder)
		.Padding(FMargin(10.f))
		.BorderImage(&GameStyle->NormalContainerBrush)
		[
			SAssignNew(ObjectImage, SBorder)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f, 0.f, 5.f, 0.f))
			.BorderImage(&GameStyle->EmptyContainerBrush)
			[
				SAssignNew(ObjectNumText, STextBlock)
				.Font(GameStyle->Font_20_Outline)
				.ColorAndOpacity(GameStyle->FontColor_Black)
				.Text(FText::FromString(FString::FromInt(i)))
			]
		];
		Gridpanel->AddSlot(i, 0)
		[
			ContainerBorder->AsShared()
		];
		
	}

}

void SSlAiShortcutWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!IsInitializeContainer)
	{
		InitializeContainer();
		IsInitializeContainer = true;
	}
}
