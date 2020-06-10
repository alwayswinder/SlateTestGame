// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"



class SBox;
class STextBlock;
class SVerticalBox;
class SSlAiNewGameWidget;
class SSlAiChooseRecordWidget;

/**
 * 
 */
struct MenuGroup;

class SLATETEST01_API SSlAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuWidget)
	{}
	SLATE_END_ARGS()
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)override;

private:
	void MenuItemOnClicked(EMenuItem::Type ItemType);
	void ChangeCulture(ECultureTeam Culture);
	void ChangeVolume(const float MusicVolume, const float SoundVolume);
	void InitializedMenuList();
	void ChooseWidget(EMenuType::Type WidgetType);
	void ResetWidgetSize(float NewWeigth, float NewHeigth);
	//UI����
	void InitializedAnimtion();
	void PlayClose(EMenuType::Type NewMenu);
	//�˳���Ϸ
	void QuitGame();
	void EnterGame();

	/**/
	const struct FSlAiMenuSlateStyle *MenuStyle;
	TSharedPtr<SBox> RootSizeBox;
	TSharedPtr<STextBlock> TitleText;
	TSharedPtr<SVerticalBox> ContentBox;
	//����Ĳ˵���
	TMap<EMenuType::Type, TSharedPtr<MenuGroup>> MenuMap;
	TSharedPtr<SCompoundWidget> GameOptionWidget;
	TSharedPtr<SSlAiNewGameWidget> NewGameWidget;
	TSharedPtr<SSlAiChooseRecordWidget> ChooseRecordWidget;
	//UI����
	FCurveSequence MenuAnimation;
	FCurveHandle MenuCurve;
	float CurrentHeight;
	bool bMenuShow;
	bool bControlLocked;
	EMenuAnim::Type AnimState;
	EMenuType::Type CurrentMenu;
};

