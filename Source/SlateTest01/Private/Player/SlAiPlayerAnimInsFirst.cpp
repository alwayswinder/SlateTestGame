// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiPlayerAnimInsFirst.h"

USlAiPlayerAnimInsFirst::USlAiPlayerAnimInsFirst()
{
	GameView = EGameViewMode::FirstMode;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerHitMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerHitMontage.FirstPlayerHitMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerFightMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerFightMontage.FirstPlayerFightMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerEatMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerEatMontage.FirstPlayerEatMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPickUpMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerPickUpMontage.FirstPlayerPickUpMontage'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> PlayerPunchMon(
		TEXT("AnimMontage'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/Animation/UpperBody/FirstPlayerPunchMontage.FirstPlayerPunchMontage'"));
	PlayerHitMontage = PlayerHitMon.Object;
	PlayerFightMontage = PlayerFightMon.Object;
	PlayerEatMontage = PlayerEatMon.Object;
	PlayerPickMontage = PlayerPickUpMon.Object;
	PlayerPunchMontage = PlayerPunchMon.Object;

}
