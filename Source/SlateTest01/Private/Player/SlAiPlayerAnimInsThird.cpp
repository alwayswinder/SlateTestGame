// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiPlayerAnimInsThird.h"
#include "SlAiPlayerCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"

USlAiPlayerAnimInsThird::USlAiPlayerAnimInsThird()
{
	GameView = EGameViewMode::ThirdMode;
	IsAir = false;
	Direction = 0.f;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerHitMontage.PlayerHitMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerFightMontage.PlayerFightMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerEatMontage.PlayerEatMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPickUpMontage.PlayerPickUpMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/Player/Animation/UpperBody/PlayerPunchMontage.PlayerPunchMontage'"));
	PlayerHitMontage = PlayerHitMon.Object;
	PlayerFightMontage = PlayerFightMon.Object;
	PlayerEatMontage = PlayerEatMon.Object;
	PlayerPickMontage = PlayerPickUpMon.Object;
	PlayerPunchMontage = PlayerPunchMon.Object;
}

void USlAiPlayerAnimInsThird::UpdateParameter()
{
	Super::UpdateParameter();

	if (PawnOwner)
	{
		IsAir = PawnOwner->GetCharacterMovement()->IsFalling();
		float PreDir = PawnOwner->GetVelocity().ToOrientationRotator().Yaw - PawnOwner->GetActorRotation().Yaw;
		if (PreDir > 180.f)
		{
			PreDir -= 360.f;
		}
		else if (PreDir < -180.f)
		{
			PreDir += 360.f;
		}
		Direction = PreDir;
	}
}
