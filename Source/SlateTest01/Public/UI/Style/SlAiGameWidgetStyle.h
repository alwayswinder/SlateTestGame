// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "SlAiGameWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLATETEST01_API FSlAiGameStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiGameStyle();
	virtual ~FSlAiGameStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiGameStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_60;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_50;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_40;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_30;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_20;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_20_Outline;

	UPROPERTY(EditAnywhere, Category = Common)
	FSlateFontInfo Font_16;

	UPROPERTY(EditAnywhere, Category = Common)
	FLinearColor FontColor_White;

	UPROPERTY(EditAnywhere, Category = Common)
	FLinearColor FontColor_Black;

	UPROPERTY(EditAnywhere, Category = Packed)
	FSlateBrush NormalContainerBrush;

	UPROPERTY(EditAnywhere, Category = Packed)
	FSlateBrush ChooseContainerBrush;

	UPROPERTY(EditAnywhere, Category = Packed)
	FSlateBrush EmptyContainerBrush;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiGameWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiGameStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
