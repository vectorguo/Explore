// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterReleaseSkill.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Explore/Characters/Monster/MonsterBase.h"
#include "Explore/Characters/Monster/MonsterController.h"

const FName BKey_Target(TEXT("Target"));

UBTTask_MonsterReleaseSkill::UBTTask_MonsterReleaseSkill(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    NodeName = "MonsterReleaseSkill";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_MonsterReleaseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto* Controller = Cast<AMonsterController>(OwnerComp.GetOuter()))
	{
		return Controller->ReleaseSkill();
	}
	return EBTNodeResult::Failed;
}

void UBTTask_MonsterReleaseSkill::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto* Controller = Cast<AMonsterController>(OwnerComp.GetOuter());
	const auto* Monster = Cast<AMonsterBase>(Controller->GetPawn());
	if (Monster->IsDead())
	{
		//怪物死亡
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		if (auto* CurrentSkill = Monster->GetSkillManager()->GetCurrentSkill())
		{
			const auto CurrentSkillState = CurrentSkill->GetSkillState();
			if (CurrentSkillState == ECharacterSkillState::ECSS_Finished)
			{
				//技能释放结束
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
			else if (CurrentSkillState == ECharacterSkillState::ECSS_Ready)
			{
				//向目标移动
				const auto* Target = Cast<AExploreCharacter>(Controller->GetBlackboardComponent()->GetValueAsObject(BKey_Target));
				if (FVector::DistSquaredXY(Monster->GetActorLocation(), Target->GetActorLocation()) <= CurrentSkill->GetReleasingRangeSquared())
				{
					//到达技能释放范围,停止移动,释放技能
					Controller->StopMovement();
					CurrentSkill->Release();
				}
			}
		}
		else
		{
			//技能被打断，释放失败
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}	
	}
}
