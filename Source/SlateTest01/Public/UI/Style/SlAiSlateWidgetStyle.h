// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "SlAiSlateWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLATETEST01_API FSlAiSlateStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiSlateStyle();
	virtual ~FSlAiSlateStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiSlateStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiSlateWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiSlateStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
