// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiPlayerController.h"
#include "SlAiPlayerCharacter.h"
#include "SlAiTypes.h"

ASlAiPlayerController::ASlAiPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	LeftUpperType = EUpperBody::Fight;
	RightUpperType = EUpperBody::Pickup;
}

void ASlAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SPCharacter = Cast<ASlAiPlayerCharacter>(GetCharacter());

	bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

}

void ASlAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASlAiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("ChangeView", IE_Pressed, this, &ASlAiPlayerController::ChangeView);
	InputComponent->BindAction("LeftEvent", IE_Pressed, this, &ASlAiPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent", IE_Released, this, &ASlAiPlayerController::LeftEventStop);
	InputComponent->BindAction("RightEvent", IE_Pressed, this, &ASlAiPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent", IE_Released, this, &ASlAiPlayerController::RightEventStop);

}

void ASlAiPlayerController::ChangeView()
{
	if (SPCharacter->IsAllowSwitch == false)	return;
	switch (SPCharacter->GameView)
	{
	case EGameViewMode::FirstMode:
		SPCharacter->ChangeView(EGameViewMode::ThirdMode);
		break;
	case EGameViewMode::ThirdMode:
		SPCharacter->ChangeView(EGameViewMode::FirstMode);
		break;
	default:
		break;
	}
}

void ASlAiPlayerController::LeftEventStart()
{
	SPCharacter->UpperBody = LeftUpperType;
}

void ASlAiPlayerController::LeftEventStop()
{
	SPCharacter->UpperBody = EUpperBody::None;
}

void ASlAiPlayerController::RightEventStart()
{
	SPCharacter->UpperBody = RightUpperType;
}

void ASlAiPlayerController::RightEventStop()
{
	SPCharacter->UpperBody = EUpperBody::None;
}
