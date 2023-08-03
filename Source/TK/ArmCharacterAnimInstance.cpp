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

void UArmCharacterAnimInstance::SetAiming(bool AimingMode)
{
	IsAiming = AimingMode;
}

void UArmCharacterAnimInstance::SetRunning(bool RunningMode)
{
	IsRunning = RunningMode;
}
