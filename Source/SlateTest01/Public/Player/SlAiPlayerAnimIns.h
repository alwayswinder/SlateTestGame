// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlAiTypes.h"
#include "SlAiPlayerAnimIns.generated.h"

class ASlAiPlayerCharacter;
/**
 * 
 */
UCLASS()
class SLATETEST01_API USlAiPlayerAnimIns : public UAnimInstance
{
	GENERATED_BODY()
public:
	USlAiPlayerAnimIns();

	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SlAiAnim")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SlAiAnim")
	FRotator SpineRotator;
protected:
	void InitPawnOwner();
	virtual void UpdateParameter();
	virtual void UpdateMontage();

protected:
	ASlAiPlayerCharacter* PawnOwner;
	UAnimMontage* PlayerHitMontage;
	UAnimMontage* PlayerFightMontage;
	UAnimMontage* PlayerPunchMontage;
	UAnimMontage* PlayerEatMontage;
	UAnimMontage* PlayerPickMontage;

	UAnimMontage* CurrentMontage;
	EGameViewMode::Type GameView;
};
