// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiGameMode.h"
#include "UI/HUD/SlAiGameHUD.h"
#include "SlAiPlayerController.h"
#include "SlAiPlayerState.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiHelper.h"
#include "SlAiGameInstance.h"
#include "SlAiDataHandle.h"
#include "Kismet/GameplayStatics.h"


ASlAiGameMode::ASlAiGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = ASlAiPlayerController::StaticClass();
	HUDClass = ASlAiGameHUD::StaticClass();
	PlayerStateClass = ASlAiPlayerState::StaticClass();
	DefaultPawnClass = ASlAiPlayerCharacter::StaticClass();

}


void ASlAiGameMode::Tick(float DeltaSeconds)
{
	
}

void ASlAiGameMode::BeginPlay()
{
	/*
	SlAiHelper::Debug(FString("RecordName: ") + SlAiDataHandle::Get()->RecordName, 30.f);
	SlAiHelper::Debug(FString("GameName: ") + Cast<USlAiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName, 
		30.f);*/
}
