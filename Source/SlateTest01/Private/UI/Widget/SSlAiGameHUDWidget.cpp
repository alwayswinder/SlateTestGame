// Fill out your copyright notice in the Description page of Project Settings.


#include "SSlAiGameHUDWidget.h"
#include "SlateOptMacros.h"
#include "SDPIScaler.h"
#include "SSlAiShortcutWidget.h"
#include "SImage.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameHUDWidget::Construct(const FArguments& InArgs)
{
	UIScale.Bind(this, &SSlAiGameHUDWidget::GetUIScale);

	ChildSlot
	[
		SNew(SDPIScaler)
		.DPIScale(UIScale)
		[
			SNew(SOverlay)

			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ShortcutWidget, SSlAiShortcutWidget)
			]
		]
	];
	
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION


float SSlAiGameHUDWidget::GetUIScale() const
{
	return GetViewPortSize().Y / 1080.f;
}

FVector2D SSlAiGameHUDWidget::GetViewPortSize() const
{
	FVector2D Result(1920.f, 1080.f);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	return Result;
}
