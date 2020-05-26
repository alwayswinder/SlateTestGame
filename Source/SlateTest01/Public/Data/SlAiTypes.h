// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECultureTeam :uint8 {
	EN,
	CN
};

namespace EMenuItem
{
	enum Type
	{
		None,
		StartGame,
		GameOption,
		QuitGame,
		NewGame,
		LoadRecord,
		StartGameGoBack,
		GameOptionGoBack,
		NewGameGoBack,
		ChooseRecordGoBack,
		EnterGame,
		EnterRecord
	};
}


class SLATETEST01_API SlAiTypes
{
public:
	SlAiTypes();
	~SlAiTypes();
};


//Ui界面
namespace EMenuType
{
	enum Type
	{
		None,
		MainMenu,
		StartGame,
		GameOption,
		NewGame,
		ChooseRecord
	};
}

//UI动画
namespace EMenuAnim
{
	enum Type
	{
		Stop,
		Close,
		Open
	};
}

//视角模式
namespace EGameViewMode
{
	enum Type
	{
		FirstMode,
		ThirdMode
	};
}

namespace EUpperBody
{
	enum Type
	{
		None,
		Hit,
		Fight,
		Eat,
		Pickup,
		Punch
	};
}