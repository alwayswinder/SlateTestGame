// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiPlayerAnimIns.h"
#include "SlAiPlayerCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "SlAiTypes.h"

USlAiPlayerAnimIns::USlAiPlayerAnimIns()
{
	Speed = 0.f;
	SpineRotator = FRotator(0.f, 0.f, 0.f);
	
}

void USlAiPlayerAnimIns::NativeUpdateAnimation(float DeltaSeconds)
{
	InitPawnOwner();
	UpdateParameter();
	UpdateMontage();
}

void USlAiPlayerAnimIns::InitPawnOwner()
{
	if (!PawnOwner)
	{
		PawnOwner = Cast<ASlAiPlayerCharacter>(TryGetPawnOwner());
	}
}

void USlAiPlayerAnimIns::UpdateParameter()
{
	if (PawnOwner)
	{
		if (!PawnOwner->GetCharacterMovement()->IsFalling())
		{
			Speed = PawnOwner->GetVelocity().Size();
		}

		float SpineDir = PawnOwner->GetActorRotation().Yaw - 90.f;
		if (SpineDir > 180.f)	SpineDir -= 360.f;
		if (SpineDir < -180.f)	SpineDir += 360.f;
		SpineRotator = FRotator(0.f, SpineDir, 90.f);
	}
}

void USlAiPlayerAnimIns::UpdateMontage()
{
	if (!PawnOwner || PawnOwner->GameView != GameView)	return;

	switch (PawnOwner->UpperBody)
	{
	case EUpperBody::None:
		if (!Montage_IsPlaying(CurrentMontage))
		{
			CurrentMontage = nullptr;
			PawnOwner->IsAllowSwitch = true;
		}
		break;
	case EUpperBody::Hit:
		if (!Montage_IsPlaying(PlayerHitMontage))
		{
			Montage_Play(PlayerHitMontage);
		}
		CurrentMontage = PlayerHitMontage;
		PawnOwner->IsAllowSwitch = false;
		break;
	case EUpperBody::Fight:
		if (!Montage_IsPlaying(PlayerFightMontage))
		{
			Montage_Play(PlayerFightMontage);
		}
		CurrentMontage = PlayerFightMontage;
		PawnOwner->IsAllowSwitch = false;
		break;
	case EUpperBody::Eat:
		if (!Montage_IsPlaying(PlayerEatMontage))
		{
			Montage_Play(PlayerEatMontage);
		}
		CurrentMontage = PlayerEatMontage;
		PawnOwner->IsAllowSwitch = false;
		break;
	case EUpperBody::Pickup:
		if (!Montage_IsPlaying(PlayerPickMontage))
		{
			Montage_Play(PlayerPickMontage);
		}
		CurrentMontage = PlayerPickMontage;
		PawnOwner->IsAllowSwitch = false;
		break;
	case EUpperBody::Punch:
		if (!Montage_IsPlaying(PlayerPunchMontage))
		{
			Montage_Play(PlayerPunchMontage);
		}
		CurrentMontage = PlayerPunchMontage;
		PawnOwner->IsAllowSwitch = false;
		break;
	default:
		break;
	}

}
