// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiGameController.h"

ASlAiGameController::ASlAiGameController()
{
	bShowMouseCursor = false;
}

void ASlAiGameController::BeginPlay()
{ 
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);
}
