// Fill out your copyright notice in the Description page of Project Settings.


#include "SlAiPlayerCharacter.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "SlAiTypes.h"

// Sets default values
ASlAiPlayerCharacter::ASlAiPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
	GameView = EGameViewMode::ThirdMode;
	UpperBody = EUpperBody::None;
	IsAllowSwitch = true;
	//
	GetCapsuleComponent()->SetCollisionProfileName(FName("PlayerProfile"));


	//ThirdMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> staticMeshThird(
		TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Player/SkMesh/Player.Player'"));
	GetMesh()->SetSkeletalMesh(staticMeshThird.Object);
	GetMesh()->bOnlyOwnerSee = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));
	//FirstMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> staticMeshFirst(
		TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/SkMesh/FirstPlayer.FirstPlayer'"));
	MeshFirst = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFirst"));
	MeshFirst->SetSkeletalMesh(staticMeshFirst.Object);
	MeshFirst->SetupAttachment(RootComponent);
	MeshFirst->bOnlyOwnerSee = true;
	MeshFirst->bCastDynamicShadow = false;
	MeshFirst->bReceivesDecals = false;
	MeshFirst->SetCollisionObjectType(ECC_Pawn);
	MeshFirst->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshFirst->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshFirst->SetRelativeLocation(FVector(0.f, 0.f, -95.f));
	MeshFirst->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.f, 0.f, -90.f)));
	//SpringCamera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 60.f);
	CameraBoom->bUsePawnControlRotation = true;
	//ThirdCamera
	ThirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	ThirdCamera->bUsePawnControlRotation = false;
	//FirstCamera
	FirstCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment(RootComponent);
	FirstCamera->bUsePawnControlRotation = true;
	FirstCamera->AddLocalOffset(FVector(0.f, 0.f, 60.f));

	//Third Anim
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird(
		TEXT("AnimBlueprint'/Game/Blueprint/ABP_PlayerThird.ABP_PlayerThird_C'"));
	GetMesh()->AnimClass = StaticAnimThird.Class;
	//First ANim
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimFirst(
		TEXT("AnimBlueprint'/Game/Blueprint/ABP_PlayerFirst.ABP_PlayerFirst_C'"));
	MeshFirst->AnimClass = StaticAnimFirst.Class;

	ThirdCamera->SetActive(true);
	FirstCamera->SetActive(false);
	GetMesh()->SetOwnerNoSee(false);
	MeshFirst->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void ASlAiPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlAiPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0 && Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
	

void ASlAiPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0 && Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASlAiPlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * GetWorld()->GetDeltaSeconds()* BaseLookUpRate);
}

void ASlAiPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ASlAiPlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * GetWorld()->GetDeltaSeconds()* BaseTurnRate);
}

void ASlAiPlayerCharacter::OnStartJump()
{
	bPressedJump = true;
}

void ASlAiPlayerCharacter::OnStopJump()
{
	bPressedJump = false;
	StopJumping();
}

void ASlAiPlayerCharacter::OnStartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ASlAiPlayerCharacter::OnStopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

// Called every frame
void ASlAiPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlAiPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASlAiPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASlAiPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASlAiPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASlAiPlayerCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASlAiPlayerCharacter::TurnAtRate);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASlAiPlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASlAiPlayerCharacter::OnStopJump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASlAiPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASlAiPlayerCharacter::OnStopRun);

}

void ASlAiPlayerCharacter::ChangeView(EGameViewMode::Type NewGameView)
{
	GameView = NewGameView;
	switch (GameView)
	{
	case EGameViewMode::FirstMode:
		FirstCamera->SetActive(true);
		ThirdCamera->SetActive(false);
		MeshFirst->SetOwnerNoSee(false);
		GetMesh()->SetOwnerNoSee(true);
		break;
	case EGameViewMode::ThirdMode:
		FirstCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		MeshFirst->SetOwnerNoSee(true);
		GetMesh()->SetOwnerNoSee(false);
		break;
	default:
		break;
	}
}

