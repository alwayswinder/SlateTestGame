// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/SlAiPlayerAnimIns.h"
#include "SlAiPlayerAnimInsThird.generated.h"

/**
 * 
 */
UCLASS()
class SLATETEST01_API USlAiPlayerAnimInsThird : public USlAiPlayerAnimIns
{
	GENERATED_BODY()
public:
	USlAiPlayerAnimInsThird();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SlAiAnim")
	bool IsAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SlAiAnim")
	float Direction;
protected:
	virtual void UpdateParameter()override;

};
