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
class UEquipmentComponent;
class UInventoryComponent;
class UGameUI;

DECLARE_DELEGATE_OneParam(FInputTakeWeaponDelegate, int)

UCLASS(config=Game)
class ATKCharacter : public ACharacter
{
	GENERATED_BODY()

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	// Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;

	// Move Controller
	UPROPERTY(VisibleDefaultsOnly, Category = Move)
	UCharacterMovementComponent* Movement;

	// Equipment
	UPROPERTY(VisibleAnywhere, Category = Equiment)
	UEquipmentComponent* Equipment;

	// Inventory
	UPROPERTY(VisibleAnywhere, Category = Inventory)
	UInventoryComponent* Inventory;

	// Projectile
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<ATKProjectile> ProjectileClass;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USceneComponent* ProjectileSpawnLocation;

	// Effect
	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystem* FireParticle;

	UPROPERTY(VisibleAnywhere)
	UGameplayStatics* GameStatic;

	// UI
	UPROPERTY()
	UGameUI* GameUI;

public:
	ATKCharacter();

protected:
	virtual void BeginPlay();

public:
	void VisibleMagazine();
	void InvisibleMagazine();
	void VisibleMesh1P();
	void InvisibleMesh1P();

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UInventoryComponent* GetInventoryComponent() const { return Inventory; }

protected:
	void TakeOnWeapon(int Index);
	void TakeOffWeapon();
	void OnZoom();
	void OnReload();
	void MoveForward(float Val);
	void MoveRight(float Val);

	void Firing(float Value);
	void Running(float Val);

	void SetSpeed(float NewSpeed);	// !!! TEMP

	// UI
	void ToggleCrossHair();
	void ToggleInventory();

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

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

	UPROPERTY()
	float DefaultWalkSpeed = 600.f;

	UPROPERTY()
	float RunWalkSpeed = DefaultWalkSpeed * 1.5f;

	UPROPERTY()
	float ZoomingWalkSpeed = DefaultWalkSpeed * 0.5f;

	UPROPERTY()
	float WalkSpeed = 600.f;

	UPROPERTY()
	float NextFire = 0.f;

	////////////////////////////////////////
	
	// Move
	UPROPERTY()
	float UpDownValue = 0.f;

	UPROPERTY()
	float LeftRightValue = 0.f;

	// State
	UPROPERTY()
	bool IsAiming;

	UPROPERTY()
	bool IsRunning;

private:
	UPROPERTY()
	UArmCharacterAnimInstance* AnimInstance;
};

