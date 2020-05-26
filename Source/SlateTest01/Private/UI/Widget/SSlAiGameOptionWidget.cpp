// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiGameOptionWidget.h"
#include "SlateOptMacros.h"
#include "SlAiWidgetStyle.h"
#include "SlAiMenuSlateWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "SBorder.h"
#include "SOverlay.h"
#include "STextBlock.h"
#include "SBoxPanel.h"
#include "SCheckBox.h"
#include "SlAiDataHandle.h"
#include "SlAiTypes.h"
#include "SlAIInternation.h"
#include "SSlider.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameOptionWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &SlAiWidgetStyle::Get().GetWidgetStyle<FSlAiMenuSlateStyle>("BPSlAiMenuStyle");

	ChangeCulture = InArgs._ChangeCulture;
	ChangeVolume = InArgs._ChangeVolume;

	//StyleInitalize();
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(300.f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->OptionBackground)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(50.f))
			[
				SNew(SVerticalBox)
//1
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SHorizontalBox)

					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)
					[
						SAssignNew(CnCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SSlAiGameOptionWidget::CnCheckBoxStateChange)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SlAiMenu", "Chinese", "Chinese"))
						]
					]

					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					.FillWidth(1.0f)
					[
						SAssignNew(EnCheckBox, SCheckBox)
						.OnCheckStateChanged(this, &SSlAiGameOptionWidget::EnCheckBoxStateChange)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SlAiMenu", "English", "English"))
						]
					]		
				]
//2
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SOverlay)
					+SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
						.Text(NSLOCTEXT("SlAiMenu", "Music", "Music"))
					] 

					+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(240.f)
						[
							SNew(SOverlay) 
							+ SOverlay::Slot()
							.HAlign(HAlign_Fill)
							.VAlign(VAlign_Center)
							.Padding(FMargin(30.f, 0.f))
							[
								SNew(SImage)
								.Image(&MenuStyle->SliderBarBrush)
							]
						]
					]
					+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.Padding(FMargin(95.f, 0.f))
					[
						SAssignNew(MuSlider, SSlider)
						.Style(&MenuStyle->SliderStyle)
						.OnValueChanged(this, &SSlAiGameOptionWidget::MusicSliderChanged)
					]					

					+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(MuTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
						.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
//3
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
						.Font(MenuStyle->Font_40)
					.ColorAndOpacity(MenuStyle->FontColor_Black)
					.Text(NSLOCTEXT("SlAiMenu", "Sound", "Sound"))
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
						SNew(SBox)
						.WidthOverride(240.f)
					[
						SNew(SOverlay)
						+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.Padding(FMargin(30.f, 0.f))
					[
						SNew(SImage)
						.Image(&MenuStyle->SliderBarBrush)
					]
					]
					]
				+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					.Padding(FMargin(95.f, 0.f))
					[
						SAssignNew(SoSlider, SSlider)
						.Style(&MenuStyle->SliderStyle)
					.OnValueChanged(this, &SSlAiGameOptionWidget::SoundSliderChanged)
					]

				+ SOverlay::Slot()
					.HAlign(HAlign_Right)
					.VAlign(VAlign_Center)
					[
						SAssignNew(SoTextBlock, STextBlock)
						.Font(MenuStyle->Font_40)
					.ColorAndOpacity(MenuStyle->FontColor_Black)
					]
				]
			]
		]
		
	];
	StyleInitalize();
}

void SSlAiGameOptionWidget::MusicSliderChanged(float Value)
{
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	//SlAiDataHandle::Get()->ResetMenuVolume(Value, -1.0f);
	ChangeVolume.ExecuteIfBound(Value, -1.0f);
}

void SSlAiGameOptionWidget::SoundSliderChanged(float Value)
{
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(Value * 100)) + FString("%")));
	//SlAiDataHandle::Get()->ResetMenuVolume(-1.0f, Value);
	ChangeVolume.ExecuteIfBound(-1.0f, Value);
}

void SSlAiGameOptionWidget::StyleInitalize()
{
	CnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	CnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	CnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	CnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	CnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	CnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);


	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBrush);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBrush);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBrush);
	switch (SlAiDataHandle::Get()->CurrnetCulture)
	{
	case ECultureTeam::EN:
		EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
		EnCheckBox->SetColorAndOpacity(MenuStyle->FontColor_White);
		CnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		CnCheckBox->SetColorAndOpacity(MenuStyle->FontColor_Black);
		break;
	case ECultureTeam::CN:
		EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
		EnCheckBox->SetColorAndOpacity(MenuStyle->FontColor_Black);
		CnCheckBox->SetIsChecked(ECheckBoxState::Checked);
		CnCheckBox->SetColorAndOpacity(MenuStyle->FontColor_White);
		break;
	default:
		break;
	}
	MuSlider->SetValue(SlAiDataHandle::Get()->MusicVolume);
	SoSlider->SetValue(SlAiDataHandle::Get()->SoundVolume);
	MuTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(SlAiDataHandle::Get()->MusicVolume * 100)) +
		FString("%")));
	SoTextBlock->SetText(FText::FromString(FString::FromInt(FMath::RoundToInt(SlAiDataHandle::Get()->SoundVolume * 100)) + 
		FString("%")));
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiGameOptionWidget::CnCheckBoxStateChange(ECheckBoxState NewState)
{
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	EnCheckBox->SetColorAndOpacity(MenuStyle->FontColor_Black);
	CnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	CnCheckBox->SetColorAndOpacity(MenuStyle->FontColor_White);
	//SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultruTeam::CN);
	ChangeCulture.ExecuteIfBound(ECultureTeam::CN);
}

void SSlAiGameOptionWidget::EnCheckBoxStateChange(ECheckBoxState NewState)
{
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	EnCheckBox->SetColorAndOpacity(MenuStyle->FontColor_White);
	CnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	CnCheckBox->SetColorAndOpacity(MenuStyle->FontColor_Black);
	//SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultruTeam::EN);
	ChangeCulture.ExecuteIfBound(ECultureTeam::EN);

}
