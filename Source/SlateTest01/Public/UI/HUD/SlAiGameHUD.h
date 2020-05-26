// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlAiGameHUD.generated.h"


class SSlAiGameHUDWidget;
/**
 * 
 */
UCLASS()
class ASlAiGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	ASlAiGameHUD();


private:
	TSharedPtr<SSlAiGameHUDWidget> GameHUDWidget;
};
