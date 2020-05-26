// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiMenuItmeWidget.h"
#include "SlateOptMacros.h"
#include "SlAiMenuSlateWidgetStyle.h"
#include "SlAiWidgetStyle.h"
#include "SBox.h"
#include "SImage.h"
#include "STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuItmeWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &SlAiWidgetStyle::Get().GetWidgetStyle<FSlAiMenuSlateStyle>("BPSlAiMenuStyle");

	OnClicked = InArgs._OnClicked;
	ItemType = InArgs._ItemType.Get();
	
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
				.ColorAndOpacity(this, &SSlAiMenuItmeWidget::GetTintColor)
			]
			+SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(InArgs._ItemText)
				.Font(MenuStyle->Font_60)
			]
		]
	];
	IsMouseButtonDown = false;
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SSlAiMenuItmeWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = true; 
	return FReply::Handled();
}


FReply SSlAiMenuItmeWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (IsMouseButtonDown)
	{
		IsMouseButtonDown = false;
		OnClicked.ExecuteIfBound(ItemType);
	}
	return FReply::Handled();
}


void SSlAiMenuItmeWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	IsMouseButtonDown = false;
}

FSlateColor SSlAiMenuItmeWidget::GetTintColor() const
{
	if (IsMouseButtonDown)
	{
		return FLinearColor(1.0f, 0.1f, 0.1f, 0.5f);
	}
	return FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
}
