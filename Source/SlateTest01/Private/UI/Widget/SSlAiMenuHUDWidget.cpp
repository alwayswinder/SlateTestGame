#include "SSlAiMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "SButton.h"
#include "SImage.h"
#include "SlAiWidgetStyle.h"
#include "SlAiMenuSlateWidgetStyle.h"
#include "SOverlay.h"
#include "Engine/Engine.h"
#include "SDPIScaler.h"
#include "SSlAiMenuWidget.h"



BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuHUDWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &SlAiWidgetStyle::Get().GetWidgetStyle<FSlAiMenuSlateStyle>("BPSlAiMenuStyle");

	UIScale.Bind(this, &SSlAiMenuHUDWidget::GetUIScale);

	ChildSlot
		[
			SNew(SDPIScaler)
			.DPIScale(UIScale)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill) 
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&MenuStyle->MenuHUDBackgroundBrush)
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)	
	//				.Expose(ImageSlot)
				[
					SAssignNew(MenuWidget, SSlAiMenuWidget)
				]
	/*			+SOverlay::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Top)
				[
					SNew(SButton)
					.OnClicked(this ,&SSlAiMenuHUDWidget::OnClick)
				]*/
			]
		];
}
/*
FReply SSlAiMenuHUDWidget::OnClick()
{
	ImageSlot->HAlign(HAlign_Right).VAlign(VAlign_Bottom);
	return FReply::Handled();
}
*/
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SSlAiMenuHUDWidget::GetUIScale() const
{
	return GetViewportSize().Y / 1080.f;
}
FVector2D SSlAiMenuHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920, 1080);
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);
	}
	return Result;
}
