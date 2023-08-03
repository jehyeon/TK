// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TKCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UMotionControllerComponent;
class UArmCharacterAnimInstance;
class UGameplayStatics;
class UParticleSytstem;
class ATKProjectile;
class UGunComponent;

UCLASS(config=Game)
class ATKCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* EquippedGun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USceneComponent* FP_MuzzleLocation;

	UPROPERTY(VisibleDefaultsOnly, Category = Move)
	UCharacterMovementComponent* Movement;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UGunComponent* PrimaryGun;

	UPROPERTY(VisibleDefaultsOnly)
	UGunComponent* SecondaryGun;

public:
	ATKCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<ATKProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect)
	UGameplayStatics* GameStatic;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Effect)
	UParticleSystem* FireParticle;

	// !!! TEMP

	UPROPERTY()
	float DefaultWalkSpeed = 600.f;

	UPROPERTY()
	float RunWalkSpeed = DefaultWalkSpeed * 1.5f;

	UPROPERTY()
	float ZoomingWalkSpeed = DefaultWalkSpeed * 0.5f;

	UPROPERTY()
	float WalkSpeed = 600.f;

	UPROPERTY()
	float RateOfFire = 0.13f;

	UPROPERTY()
	float NextFire = 0.f;
	////////////////////////////////////////

	UPROPERTY()
	float UpDownValue = 0.f;

	UPROPERTY()
	float LeftRightValue = 0.f;

	UPROPERTY()
	bool IsAiming = false;

	UPROPERTY()
	bool IsRunning = false;
public:
	void InvisibleMagazine();
	void VisibleMagazine();

protected:
	void OnZoom();
	void OnReload();
	void MoveForward(float Val);
	void MoveRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void Firing(float Value);
	void Running(float Val);
	
	void SetSpeed(float NewSpeed);	// !!! TEMP

	void ToggleCrossHair();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

private:
	UArmCharacterAnimInstance* AnimInstance;

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

