// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"
#include "SlateBrush.h"
#include "SlateFontInfo.h"
#include "SlateSound.h"
#include "SlAiMenuSlateWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLATETEST01_API FSlAiMenuSlateStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiMenuSlateStyle();
	virtual ~FSlAiMenuSlateStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiMenuSlateStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = MenuHUD)
	FSlateBrush MenuHUDBackgroundBrush;

	UPROPERTY(EditAnywhere, Category = Menu)
	FSlateBrush MenuCenterBackgroundBrush;

	UPROPERTY(EditAnywhere, Category = Menu)
	FSlateBrush MenuLeftIconBrush;

	UPROPERTY(EditAnywhere, Category = Menu)
	FSlateBrush MenuRightIconBrush;

	UPROPERTY(EditAnywhere, Category = Menu)
	FSlateBrush MenuTitleBorderBrush;

	UPROPERTY(EditAnywhere, Category = MenuItem)
	FSlateBrush MenuItemBrush;

	UPROPERTY(EditAnywhere, Category = GameOption)
	FSlateBrush OptionBackground;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_60;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_40;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_30;

	UPROPERTY(EditAnywhere, Category = Common)
	FLinearColor FontColor_Black;

	UPROPERTY(EditAnywhere, Category = Common)
	FLinearColor FontColor_White;

	UPROPERTY(EditAnywhere, Category = GameOption)
	FSlateBrush CheckedBoxBrush;

	UPROPERTY(EditAnywhere, Category = GameOption)
	FSlateBrush UnCheckedBoxBrush;

	UPROPERTY(EditAnywhere, Category = GameOption)
	FSlateBrush SliderBarBrush;

	UPROPERTY(EditAnywhere, Category = GameOption)
	FSliderStyle SliderStyle;

	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound StartGameSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound ExitGameSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound MenuItemChangeSound;

	UPROPERTY(EditAnywhere, Category = Sound)
	FSlateSound MenuBackgroundMusic;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiMenuSlateWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiMenuSlateStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
