// Copyright Epic Games, Inc. All Rights Reserved.

#include "TKCharacter.h"
#include "TKProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
//#include "Kismet/GameplayStatics.h"
#include "ArmCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "TKHUD.h"
#include "Components/SkinnedMeshComponent.h"
#include "GunComponent.h"

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

	PrimaryGun = CreateDefaultSubobject<UGunComponent>(TEXT("PrimaryGun"));
	SecondaryGun = CreateDefaultSubobject<UGunComponent>(TEXT("SecondaryGun"));

	EquippedGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	EquippedGun->SetupAttachment(Mesh1P, TEXT("SOCKET_Weapon"));
	EquippedGun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FirstPersonCameraComponent);
	FP_MuzzleLocation->SetRelativeLocation(FVector(60.f, 1.f, -3.f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, -5.0f);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FP(TEXT("ParticleSystem'/LPSPSample/LPSPSample/Art/Effects/PS_MFlash.PS_MFlash'"));
	if (FP.Succeeded())
	{
		FireParticle = FP.Object;
	}
}

void ATKCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// temp
	/*f (SM.Succeeded())
	{*/
		//UE_LOG(LogTemp, Warning, TEXT("로드 성공"));
		//PrimaryGun->SetMesh(SM.Object);
	//}
	EquippedGun->SetSkeletalMesh(PrimaryGun->GetMesh());
	/////////////////////////////////////////////////////
	// 
	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	EquippedGun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SOCKET_Weapon"));
	EquippedGun->SetRelativeTransform(FTransform(FVector(-1.25f, -3.f, -3.f)));

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

void ATKCharacter::InvisibleMagazine()
{
	EquippedGun->HideBone(EquippedGun->GetBoneIndex(FName("b_gun_mag")), EPhysBodyOp::PBO_None);
}

void ATKCharacter::VisibleMagazine()
{
	EquippedGun->UnHideBone(EquippedGun->GetBoneIndex(FName("b_gun_mag")));
}

void ATKCharacter::OnZoom()
{
	//GunMesh->HideBone(4, PBO_None);

	if (IsRunning && !IsAiming)
	{
		return;
	}

	ToggleCrossHair();
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

		// temp
		PrimaryGun->EquipMagazine();

		AnimInstance->PlayReloadMontage();
	}
}

void ATKCharacter::MoveForward(float Value)
{
	const FRotator SpawnRotation = GetControlRotation();
	//DrawDebugLine(GetWorld(), 
	//	FP_MuzzleLocation->GetComponentLocation(), 
	//	FP_MuzzleLocation->GetComponentLocation() + SpawnRotation.RotateVector(GunOffset) * 1000,
	//	FColor::Red, false, 0.1f, 0, 1.f);

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

	if (Value < 1.f || IsRunning)
	{
		return;
	}

	if (NextFire < RateOfFire)
	{
		return;
	}

	// temp 탄창 확인
	if (!PrimaryGun->Fire())
	{
		return;
	}

	NextFire = 0.f;

	if (FireParticle)
	{
		GameStatic->SpawnEmitterAttached(FireParticle, EquippedGun, FName("Muzzle"));
	}

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
			World->SpawnActor<ATKProjectile>(ProjectileClass, SpawnLocation, SpawnRotation.RotateVector(GunOffset).Rotation(), ActorSpawnParams);
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

void ATKCharacter::ToggleCrossHair()
{
	Cast<ATKHUD>(UGameplayStatics::GetPlayerController(GetOwner(), 0)->GetHUD())->ToggleCrossHair();
}
