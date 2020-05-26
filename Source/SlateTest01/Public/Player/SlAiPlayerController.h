// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlAiTypes.h"
#include "SlAiPlayerController.generated.h"


class ASlAiPlayerCharacter;
/**
 * 
 */
UCLASS()
class SLATETEST01_API ASlAiPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASlAiPlayerController();

	virtual void BeginPlay()override;

	virtual void Tick(float DeltaSeconds)override;

	virtual void SetupInputComponent()override;
public:
	ASlAiPlayerCharacter* SPCharacter;
	
	

private:
	void ChangeView();
	void LeftEventStart();
	void LeftEventStop();
	void RightEventStart();
	void RightEventStop();
private:
	EUpperBody::Type LeftUpperType;
	EUpperBody::Type RightUpperType;
};
