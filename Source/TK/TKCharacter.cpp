// Copyright Epic Games, Inc. All Rights Reserved.

#include "TKCharacter.h"
#include "TKProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "ArmCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATKCharacter

ATKCharacter::ATKCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	// 줌 상태와 에임 일치 (별도의 카메라 추가 고려)
	Mesh1P->SetRelativeLocation(FVector(0.f, -1.27f, -2.75f));
	Mesh1P->SetRelativeRotation(FRotator(0.f, -89.2f, 2.f));
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(false);			// otherwise won't be visible in the multiplayer
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(Mesh1P, TEXT("SOCKET_Weapon"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

}

void ATKCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SOCKET_Weapon"));
	FP_Gun->SetRelativeTransform(FTransform(FVector(-1.25f, -3.f, -3.f)));

	Mesh1P->SetHiddenInGame(false, true);
	AnimInstance = Cast<UArmCharacterAnimInstance>(Mesh1P->GetAnimInstance());

	Movement = Cast<ACharacter>(this)->GetCharacterMovement();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATKCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// 이벤트 바인드
	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &ATKCharacter::OnZoom);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATKCharacter::OnReload);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATKCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATKCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATKCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATKCharacter::LookUpAtRate);

	PlayerInputComponent->BindAxis("Fire", this, &ATKCharacter::Firing);
	PlayerInputComponent->BindAxis("Run", this, &ATKCharacter::Running);
}

void ATKCharacter::OnZoom()
{
	if (IsRunning && !IsAiming)
	{
		return;
	}

	// Default Toggle
	if (IsAiming)
	{
		SetSpeed(DefaultWalkSpeed);
	}
	else
	{
		SetSpeed(ZoomingWalkSpeed);
	}

	IsAiming = !IsAiming;

	if (AnimInstance)
	{
		AnimInstance->SetAiming(IsAiming);
	}
}

void ATKCharacter::OnReload()
{
	if (AnimInstance)
	{
		if (IsAiming)
		{
			OnZoom();
		}

		AnimInstance->PlayReloadMontage();
	}
}

void ATKCharacter::MoveForward(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Movement->MaxWalkSpeed);
	UpDownValue = Value;
	AddMovementInput(GetActorForwardVector(), Value);
}

void ATKCharacter::MoveRight(float Value)
{
	LeftRightValue = Value;
	AddMovementInput(GetActorRightVector(), Value);
}

void ATKCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATKCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATKCharacter::Running(float Val)
{
	// !!! NEED TO UPDATE
	if (UpDownValue >= 1.f && Val >= 1.f)
	{
		IsRunning = true;

		if (IsAiming)
		{
			OnZoom();
		}

		SetSpeed(RunWalkSpeed);
	}
	else
	{
		IsRunning = false;

		if (IsAiming)
		{
			SetSpeed(ZoomingWalkSpeed);
		}
		else
		{
			SetSpeed(DefaultWalkSpeed);
		}
	}

	if (AnimInstance)
	{
		AnimInstance->SetRunning(IsRunning);
	}
}

void ATKCharacter::Firing(float Value)
{
	NextFire += GetWorld()->GetDeltaSeconds();

	if (Value < 1.f)
	{
		return;
	}

	if (NextFire < RateOfFire)
	{
		return;
	}
	
	NextFire = 0.f;

	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ATKProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	if (AnimInstance)
	{
		AnimInstance->PlayFireMontage();
	}
}

void ATKCharacter::SetSpeed(float NewSpeed)
{
	Movement->MaxWalkSpeed = NewSpeed;
}