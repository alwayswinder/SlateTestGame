// Fill out your copyright notice in the Description page of Project Settings.

#include "SSlAiMenuWidget.h"
#include "SlateOptMacros.h"
#include "SBox.h"
#include "SlAiWidgetStyle.h"
#include "SlAiMenuSlateWidgetStyle.h"
#include "SImage.h"
#include "STextBlock.h"
#include "SSlAiMenuItmeWidget.h"
#include "SlAiHelper.h"
#include "SSlAiGameOptionWidget.h"
#include "SlAiDataHandle.h"
#include "SSlAiNewGameWidget.h"
#include "SSlAiChooseRecordWidget.h"
#include "Kismet/GameplayStatics.h"


struct MenuGroup
{
	FText MenuName;
	float MenuHeight;
	TArray<TSharedPtr<SCompoundWidget>> ChildWidget;
	MenuGroup(const FText Name, const float Height, TArray<TSharedPtr<SCompoundWidget>>*Children)
	{
		MenuName = Name;
		MenuHeight = Height;
		for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It(*Children); It; ++It)
		{
			ChildWidget.Add(*It);
		}
	}
};




BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuWidget::Construct(const FArguments& InArgs)
{
	MenuStyle = &SlAiWidgetStyle::Get().GetWidgetStyle<FSlAiMenuSlateStyle>("BPSlAiMenuStyle");

	//FInternationalization::Get().SetCurrentLanguage(TEXT("en"));
	//FInternationalization::Get().SetCurrentLanguage(TEXT("ch")); 

	FSlateApplication::Get().PlaySound(MenuStyle->MenuBackgroundMusic);

	ChildSlot
	[
		SAssignNew(RootSizeBox, SBox)
		[
			SNew(SOverlay)
			//背景图片
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.f,50.f,0.f,0.f))
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuCenterBackgroundBrush)
			]
			//左边框
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuLeftIconBrush)
			]
			//右边框
			+ SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 25.f, 0.f, 0.f))
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuRightIconBrush)
			]
			//菜单标题
			+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				[
					SNew(SBox)
					.WidthOverride(400.f)
					.HeightOverride(100.f)
					[
						SNew(SBorder)
						.BorderImage(&MenuStyle->MenuTitleBorderBrush)
						.HAlign(HAlign_Center)
						.VAlign(VAlign_Center)
						[
							SAssignNew(TitleText, STextBlock)
							.Font(SlAiWidgetStyle::Get().GetFontStyle("MenuItemFont"))
							.Text(NSLOCTEXT("SlAiMenu", "Menu", "Menu"))
						]
					]
				]
			//菜单内部控件
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.f, 30.f, 0.f, 0.f))
			[
				SAssignNew(ContentBox, SVerticalBox)
				
			]
		]
	];
	
	InitializedMenuList();
	InitializedAnimtion();
	
}

void SSlAiMenuWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, 
	const float InDeltaTime)
{
	switch (AnimState)
	{
	case EMenuAnim::Stop:
		break;
	case EMenuAnim::Close:
		if (MenuAnimation.IsPlaying())
		{
			ResetWidgetSize(MenuCurve.GetLerp()*600.f, -1.f);
			if (MenuCurve.GetLerp() < 0.6f && bMenuShow)
			{
				ChooseWidget(EMenuType::None);
			}
		}
		else
		{
			AnimState = EMenuAnim::Open;
			MenuAnimation.Play(this->AsShared());
		}
		break;
	case EMenuAnim::Open:
		if (MenuAnimation.IsPlaying())
		{
			ResetWidgetSize(MenuCurve.GetLerp()*600.f, CurrentHeight);
			if (MenuCurve.GetLerp() > 0.4f && !bMenuShow)
			{
				ChooseWidget(CurrentMenu);
			}
		}
		if (MenuAnimation.IsAtEnd())
		{
			AnimState = EMenuAnim::Stop;
			bControlLocked = false;
		}
		break;
	default:
		break;
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiMenuWidget::MenuItemOnClicked(EMenuItem::Type ItemType)
{
	if (bControlLocked)
		return;

	bControlLocked = true;

	switch (ItemType)
	{
	case EMenuItem::StartGame:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::GameOption:
		PlayClose(EMenuType::GameOption);
		break;
	case EMenuItem::QuitGame:
		SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), 
			MenuStyle->ExitGameSound,this, &SSlAiMenuWidget::QuitGame);
		break;
	case EMenuItem::NewGame:
		PlayClose(EMenuType::NewGame);
		break;
	case EMenuItem::LoadRecord:
		PlayClose(EMenuType::ChooseRecord);
		break;
	case EMenuItem::StartGameGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::GameOptionGoBack:
		PlayClose(EMenuType::MainMenu);
		break;
	case EMenuItem::NewGameGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::ChooseRecordGoBack:
		PlayClose(EMenuType::StartGame);
		break;
	case EMenuItem::EnterGame:
		if (NewGameWidget->AllowEnterGame())
		{
			SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(),
					MenuStyle->StartGameSound, this, &SSlAiMenuWidget::EnterGame);	
		}
		else
		{
			bControlLocked = false;
		}
		break;
	case EMenuItem::EnterRecord:
		ChooseRecordWidget->UpdateRecordName();
		bControlLocked = false;
		SlAiHelper::PlayerSoundAndCall(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(),
			MenuStyle->StartGameSound, this, &SSlAiMenuWidget::EnterGame);
		break;
	}
}

void SSlAiMenuWidget::ChangeCulture(ECultureTeam Culture)
{
	SlAiDataHandle::Get()->ChangeLocalizationCulture(Culture);
}

void SSlAiMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	SlAiDataHandle::Get()->ResetMenuVolume(MusicVolume, SoundVolume);
}

void SSlAiMenuWidget::InitializedMenuList()
{
	RootSizeBox->SetWidthOverride(600.f);
	RootSizeBox->SetHeightOverride(510.f);

	//主界面
	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
	MainMenuList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "StartGame", 
		"StartGame")).ItemType(EMenuItem::StartGame).OnClicked(this,
			&SSlAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "GameOption", 
		"GameOption")).ItemType(EMenuItem::GameOption).OnClicked(this,
			&SSlAiMenuWidget::MenuItemOnClicked));
	MainMenuList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "QuitGame", 
		"QuitGame")).ItemType(EMenuItem::QuitGame).OnClicked(this, 
			&SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::MainMenu, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "Menu",
		"Menu"),510.f, &MainMenuList)));

	//开始游戏
	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
	StartGameList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "NewGame", 
		"NewGame")).ItemType(EMenuItem::NewGame).OnClicked(this, 
			&SSlAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "LoadRecord", 
		"LoadRecord")).ItemType(EMenuItem::LoadRecord).OnClicked(this, 
			&SSlAiMenuWidget::MenuItemOnClicked));
	StartGameList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", 
		"GoBack")).ItemType(EMenuItem::StartGameGoBack).OnClicked(this,
			&SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::StartGame, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "StartGame", 
		"StartGame"),510.f, &StartGameList)));

	//游戏设置界面
	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
	SAssignNew(GameOptionWidget, SSlAiGameOptionWidget)
		.ChangeCulture(this, &SSlAiMenuWidget::ChangeCulture)
		.ChangeVolume(this, &SSlAiMenuWidget::ChangeVolume);
	GameOptionList.Add(GameOptionWidget);
	GameOptionList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType
	(EMenuItem::GameOptionGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::GameOption, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "GameOption", "GameOption"),
		610.f, &GameOptionList)));

	//新游戏
	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
	SAssignNew(NewGameWidget, SSlAiNewGameWidget);
	NewGameList.Add(NewGameWidget);
	NewGameList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "EnterGame", "EnterGame")).ItemType
	(EMenuItem::EnterGame).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	NewGameList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType
	(EMenuItem::NewGameGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::NewGame, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "NewGame", "NewGame"),
		510.f, &NewGameList)));

	//选择存档
	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
	SAssignNew(ChooseRecordWidget, SSlAiChooseRecordWidget);
	ChooseRecordList.Add(ChooseRecordWidget);
	ChooseRecordList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "EnterRecord", "EnterRecord")).ItemType
	(EMenuItem::EnterRecord).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	ChooseRecordList.Add(SNew(SSlAiMenuItmeWidget).ItemText(NSLOCTEXT("SlAiMenu", "GoBack", "GoBack")).ItemType
	(EMenuItem::ChooseRecordGoBack).OnClicked(this, &SSlAiMenuWidget::MenuItemOnClicked));
	MenuMap.Add(EMenuType::ChooseRecord, MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu", "LoadRecord", "LoadRecord"),
		510.f, &ChooseRecordList)));

}

void SSlAiMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	//是否已经显示菜单
	bMenuShow = WidgetType != EMenuType::None;


	ContentBox->ClearChildren();
	if (WidgetType == EMenuType::None)	return;
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget); It; ++It)
	{
		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];
	}
	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);

	//ResetWidgetSize(600.f, (*MenuMap.Find(WidgetType))->MenuHeight);
}

void SSlAiMenuWidget::ResetWidgetSize(float NewWeigth, float NewHeigth)
{
	RootSizeBox->SetWidthOverride(NewWeigth);
	if (NewHeigth < 0)	return;
	RootSizeBox->SetHeightOverride(NewHeigth);
}

void SSlAiMenuWidget::InitializedAnimtion()
{
	const float StartDelay = 0.3f;
	const float AnimDuration = 0.6f;
	MenuAnimation = FCurveSequence();
	MenuCurve = MenuAnimation.AddCurve(StartDelay, AnimDuration, ECurveEaseFunction::QuadInOut);

	ResetWidgetSize(600.f, 500.f);

	ChooseWidget(EMenuType::MainMenu);
	
	bControlLocked = false;
	AnimState = EMenuAnim::Stop;
	MenuAnimation.JumpToEnd();


}

void SSlAiMenuWidget::PlayClose(EMenuType::Type NewMenu)
{
	CurrentMenu = NewMenu; 
	CurrentHeight = (*MenuMap.Find(NewMenu))->MenuHeight;
	AnimState = EMenuAnim::Close;
	MenuAnimation.PlayReverse(this->AsShared());

	FSlateApplication::Get().PlaySound(MenuStyle->MenuItemChangeSound);

}


void SSlAiMenuWidget::QuitGame()
{
	UGameplayStatics::GetPlayerController(GWorld, 0)->ConsoleCommand("quit");
}

void SSlAiMenuWidget::EnterGame()
{
	bControlLocked = false;
	UGameplayStatics::OpenLevel(UGameplayStatics::GetPlayerController(GWorld, 0)->GetWorld(), FName("GameMap"));
}
