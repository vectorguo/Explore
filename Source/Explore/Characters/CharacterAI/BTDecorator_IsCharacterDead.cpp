// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsCharacterDead.h"

#include "Explore/Characters/ExploreCharacter.h"

UBTDecorator_IsCharacterDead::UBTDecorator_IsCharacterDead(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "IsCharacterDead";
}

bool UBTDecorator_IsCharacterDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AController* Controller = Cast<AController>(OwnerComp.GetOwner());
	if (Controller)
	{
		const auto* Character = Cast<AExploreCharacter>(Controller->GetPawn());
		if (Character)
		{
			return Character->IsDead();
		}
	}
	return false;
}
