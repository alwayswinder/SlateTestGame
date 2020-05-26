// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiGameController.generated.h"

/**
 * 
 */
UCLASS()
class SLATETEST01_API ASlAiGameController : public APlayerController
{
	GENERATED_BODY()
public:
	ASlAiGameController();

protected:
	virtual void BeginPlay()override;
	
};
