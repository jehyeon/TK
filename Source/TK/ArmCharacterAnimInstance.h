// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ArmCharacterAnimInstance.generated.h"

UCLASS()
class TK_API UArmCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UArmCharacterAnimInstance();

	UFUNCTION()
	void AnimNotify_InvisibleMagazine();

	UFUNCTION()
	void AnimNotify_VisibleMagazine();

	UFUNCTION()
	void AnimNotify_VisibleMesh1P();

	UFUNCTION()
	void AnimNotify_InvisibleMesh1P();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayFireMontage();
	void PlayReloadMontage();
	void PlayHolsterMontage();
	void PlayUnholsterMontage();

	void SetAiming(bool AimingMode);
	void SetRunning(bool RunningMode);
	void SetHolster(bool HolsterMode);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsAiming;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsRunning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsHolster;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Horizontal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* HolsterMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* UnholsterMontage;
};
