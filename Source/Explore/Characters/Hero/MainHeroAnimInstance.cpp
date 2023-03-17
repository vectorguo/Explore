// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHeroAnimInstance.h"
#include "MainHero.h"
#include "MainHeroController.h"
#include "GameFramework/PawnMovementComponent.h"

void UMainHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Hero = Cast<AMainHero>(Pawn);
		}
	}
}

void UMainHeroAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		if (Pawn)
		{
			Hero = Cast<AMainHero>(Pawn);
		}
	}

	if (Pawn)
	{
		const FVector Speed = Pawn->GetVelocity();
		const FVector LateralSpeed(Speed.X, Speed.Y, 0.0f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();
	}
}