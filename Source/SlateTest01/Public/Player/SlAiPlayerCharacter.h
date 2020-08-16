// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiTypes.h"
#include "GameFramework/Character.h"
#include "SlAiPlayerCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SLATETEST01_API ASlAiPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ASlAiPlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ChangeView(EGameViewMode::Type NewGameView);

	/*Value*/
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
	UCameraComponent* ThirdCamera;
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
	UCameraComponent* FirstCamera;

	EGameViewMode::Type GameView;
	EUpperBody::Type UpperBody;
	bool IsAllowSwitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUpAtRate(float Value);
	void Turn(float Value);
	void TurnAtRate(float Value);
	void OnStartJump();
	void OnStopJump();
	void OnStartRun();
	void OnStopRun();
	
private:
	/*Value*/
	UPROPERTY(VisibleDefaultsOnly, Category = "SlAi")
	USkeletalMeshComponent* MeshFirst;
	float BaseLookUpRate;
	float BaseTurnRate;
};
