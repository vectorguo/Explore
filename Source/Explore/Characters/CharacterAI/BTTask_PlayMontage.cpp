// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PlayMontage.h"

#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/Monster/MonsterController.h"

UBTTask_PlayMontage::UBTTask_PlayMontage(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    NodeName = "PlayMontage";
    bNotifyTick = true;
	PlayRate = 1.0f;
}

EBTNodeResult::Type UBTTask_PlayMontage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* Controller = Cast<AMonsterController>(OwnerComp.GetOuter()))
	{
		if (auto* Character = Cast<AExploreCharacter>(Controller->GetPawn()))
		{
			Character->PlayMontage(*MontageName, PlayRate);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}