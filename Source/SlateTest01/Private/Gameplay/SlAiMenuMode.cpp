// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiMenuMode.h"
#include "SlAiMenuController.h"
#include "SlAiMenuHUD.h"
#include "SlAiGameInstance.h"
#include "Kismet/GameplayStatics.h"




ASlAiMenuMode::ASlAiMenuMode()
{
	PlayerControllerClass = ASlAiMenuController::StaticClass();
	HUDClass = ASlAiMenuHUD::StaticClass();

}

void ASlAiMenuMode::BeginPlay()
{
	Cast<USlAiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName = FString("SlAiStudy");
}
