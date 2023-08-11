// Copyright Epic Games, Inc. All Rights Reserved.

#include "TKCharacter.h"
#include "TKProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ArmCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystem.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "TKHUD.h"
#include "Components/SkinnedMeshComponent.h"
#include "GunComponent.h"
#include "EquipmentComponent.h"
#include "InventoryComponent.h"
#include "GunStatComponent.h"
#include "MagazineComponent.h"
#include "TKGameMode.h"
#include "GameUI.h"

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

	// Camera Component 생성
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Mesh Component 생성
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	// 줌 상태와 에임 일치 (별도의 카메라 추가 고려)
	Mesh1P->SetRelativeLocation(FVector(0.f, -1.27f, -2.75f));
	Mesh1P->SetRelativeRotation(FRotator(0.f, -89.2f, 2.f));
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	WeaponMesh->SetupAttachment(Mesh1P, TEXT("SOCKET_Weapon"));
	WeaponMesh->bCastDynamicShadow = false;
	WeaponMesh->CastShadow = false;

	Equipment = CreateDefaultSubobject<UEquipmentComponent>(TEXT("Equipment"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	// Projectile 스폰 위치 설정
	ProjectileSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	ProjectileSpawnLocation->SetupAttachment(FirstPersonCameraComponent);
	ProjectileSpawnLocation->SetRelativeLocation(FVector(60.f, 1.f, -3.f));

	// temp
	GunOffset = FVector(100.0f, 0.0f, -5.0f);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> FP(TEXT("ParticleSystem'/LPSPSample/LPSPSample/Art/Effects/PS_MFlash.PS_MFlash'"));
	if (FP.Succeeded())
	{
		FireParticle = FP.Object;
	}

	//EquippedWeaponIndex = -1;

	IsAiming = false;
	IsRunning = false;
}

void ATKCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	WeaponMesh->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("SOCKET_Weapon"));
	WeaponMesh->SetRelativeTransform(FTransform(FVector(-1.25f, -3.f, -3.f)));

	Mesh1P->SetHiddenInGame(false, true);
	AnimInstance = Cast<UArmCharacterAnimInstance>(Mesh1P->GetAnimInstance());

	Movement = Cast<ACharacter>(this)->GetCharacterMovement();

	InvisibleMesh1P();

	// UI
	ATKGameMode* GameMode = Cast<ATKGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameUI = GameMode->GetGameUI();
	if (GameUI)
	{
		GameUI->SetPlayerController(Cast<APlayerController>(GetController()));
	}
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

	PlayerInputComponent->BindAction<FInputTakeWeaponDelegate>("TakePrimaryWeapon", IE_Pressed, this, &ATKCharacter::TakeOnWeapon, 0);
	PlayerInputComponent->BindAction<FInputTakeWeaponDelegate>("TakeSecondaryWeapon", IE_Pressed, this, &ATKCharacter::TakeOnWeapon, 1);
	PlayerInputComponent->BindAction("UnTakeWeapon", IE_Pressed, this, &ATKCharacter::TakeOffWeapon);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATKCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATKCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Fire", this, &ATKCharacter::Firing);
	PlayerInputComponent->BindAxis("Run", this, &ATKCharacter::Running);

	PlayerInputComponent->BindAction("ToggleInventory", IE_Pressed, this, &ATKCharacter::ToggleInventory);
}

void ATKCharacter::VisibleMagazine()
{
	WeaponMesh->UnHideBone(WeaponMesh->GetBoneIndex(FName("b_gun_mag")));
}

void ATKCharacter::InvisibleMagazine()
{
	WeaponMesh->HideBone(WeaponMesh->GetBoneIndex(FName("b_gun_mag")), EPhysBodyOp::PBO_None);
}

void ATKCharacter::VisibleMesh1P()
{
	Mesh1P->SetVisibility(true, true);
}

void ATKCharacter::InvisibleMesh1P()
{
	Mesh1P->SetVisibility(false, true);
}

void ATKCharacter::TakeOnWeapon(int Index)
{
	// 들고 있는 무기가 없는 경우
	if (!Equipment->IsExistWeapon(Index))
	{
		return;
	}

	if (Equipment->IsTakeWeapon(Index))
	{
		return;
	}

	Equipment->TakeOnWeapon(Index);

	// Mesh 설정
	WeaponMesh->SetSkeletalMesh(Equipment->GetEquippedWeaponMesh());

	// 애니메이션 재생
	AnimInstance->PlayUnholsterMontage();
}

void ATKCharacter::TakeOffWeapon()
{
	if (!Equipment->IsTakeWeapon())
	{
		return;
	}

	AnimInstance->PlayHolsterMontage();
}

void ATKCharacter::OnZoom()
{
	if (!Equipment->IsTakeWeapon())
	{
		return;
	}

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
	if (!Equipment->IsTakeWeapon())
	{
		return;
	}

	// temp
	Equipment->GetEquippedWeapon()->EquipMagazine();

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
	const FRotator SpawnRotation = GetControlRotation();

	UpDownValue = Value;
	AddMovementInput(GetActorForwardVector(), Value);
}

void ATKCharacter::MoveRight(float Value)
{
	LeftRightValue = Value;
	AddMovementInput(GetActorRightVector(), Value);
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

	if (!Equipment->IsTakeWeapon())
	{
		return;
	}

	// temp
	UGunComponent* EquippedGun = Equipment->GetEquippedWeapon();
	float RateOfFire = EquippedGun->GetStat()->GetRateOfFire();

	if (NextFire < RateOfFire)
	{
		return;
	}

	// 탄창 확인
	if (!EquippedGun->Fire())
	{
		return;
	}

	NextFire = 0.f;

	if (FireParticle)
	{
		GameStatic->SpawnEmitterAttached(FireParticle, WeaponMesh, FName("Muzzle"));
	}

	// try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetControlRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = ((ProjectileSpawnLocation != nullptr) ? ProjectileSpawnLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

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

void ATKCharacter::ToggleInventory()
{
	if (GameUI)
	{
		GameUI->ToggleInventory();
	}
}
