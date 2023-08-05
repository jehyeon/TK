// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmCharacterAnimInstance.h"
#include "TKCharacter.h"

UArmCharacterAnimInstance::UArmCharacterAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> FM(TEXT("AnimMontage'/Game/Character/AM_Fire.AM_Fire'"));
	if (FM.Succeeded())
	{
		FireMontage = FM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> RM(TEXT("AnimMontage'/Game/Character/AM_Reload.AM_Reload'"));
	if (RM.Succeeded())
	{
		ReloadMontage = RM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HM(TEXT("AnimMontage'/Game/Character/AM_Holster.AM_Holster'"));
	if (HM.Succeeded())
	{
		HolsterMontage = HM.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> UHM(TEXT("AnimMontage'/Game/Character/AM_Unholster.AM_Unholster'"));
	if (UHM.Succeeded())
	{
		UnholsterMontage = UHM.Object;
	}

	IsAiming = false;
	IsRunning = false;
	IsHolster = false;
}

void UArmCharacterAnimInstance::AnimNotify_InvisibleMagazine()
{
	// not good
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		auto Character = Cast<ATKCharacter>(Pawn);
		if (Character)
		{
			Character->InvisibleMagazine();
		}
	}
}

void UArmCharacterAnimInstance::AnimNotify_VisibleMagazine()
{
	// not good
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		auto Character = Cast<ATKCharacter>(Pawn);
		if (Character)
		{
			Character->VisibleMagazine();
		}
	}
}

void UArmCharacterAnimInstance::AnimNotify_VisibleMesh1P()
{
	// not good
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		auto Character = Cast<ATKCharacter>(Pawn);
		if (Character)
		{
			Character->VisibleMesh1P();
		}
	}
}

void UArmCharacterAnimInstance::AnimNotify_InvisibleMesh1P()
{
	// not good
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		auto Character = Cast<ATKCharacter>(Pawn);
		if (Character)
		{
			Character->InvisibleMesh1P();
		}
	}
}

void UArmCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		auto Character = Cast<ATKCharacter>(Pawn);
		if (Character)
		{
			Horizontal = Character->LeftRightValue;
			Vertical = Character->UpDownValue;
		}
	}
}

void UArmCharacterAnimInstance::PlayFireMontage()
{
	//UE_LOG(LogTemp, Warning, TEXT("1"));
	//if (!Montage_IsPlaying(FireMontage))
	//{
		Montage_Play(FireMontage, 1.f);
	//}
}

void UArmCharacterAnimInstance::PlayReloadMontage()
{
	if (!Montage_IsPlaying(ReloadMontage))
	{
		Montage_Play(ReloadMontage, 1.f);
	}
}

void UArmCharacterAnimInstance::PlayHolsterMontage()
{
	Montage_Play(HolsterMontage, 1.f);
}

void UArmCharacterAnimInstance::PlayUnholsterMontage()
{
	Montage_Play(UnholsterMontage, 1.f);
}

void UArmCharacterAnimInstance::SetAiming(bool AimingMode)
{
	IsAiming = AimingMode;
}

void UArmCharacterAnimInstance::SetRunning(bool RunningMode)
{
	IsRunning = RunningMode;
}

void UArmCharacterAnimInstance::SetHolster(bool HolsterMode)
{
	IsHolster = HolsterMode;
}
