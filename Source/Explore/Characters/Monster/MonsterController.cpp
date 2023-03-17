// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterController.h"

#include "MonsterBase.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Stronghold/MonsterStronghold.h"
#include "Explore/Table/TableMonster.h"
#include "Kismet/KismetMathLibrary.h"

const FName BlackboardKey_BirthPosition(TEXT("BirthPosition"));
const FName BlackboardKey_HasTarget(TEXT("HasTarget"));
const FName BlackboardKey_Target(TEXT("Target"));

void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//创建Blackboard
	Blackboard = NewObject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
	Blackboard->RegisterComponent();

	//记录出生位置
	BirthPosition = InPawn->GetActorLocation();

	//获取所属Monster
	OwnerMonster = Cast<AMonsterBase>(GetPawn());
}

void AMonsterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero())
	{
		const auto* MonsterConfig = FTableMonster::GetRow(OwnerMonster->GetMonsterID());
		if (Blackboard->GetValueAsBool(BlackboardKey_HasTarget))
		{
			//检测英雄是否离开视野范围
			auto* WarningVolume = OwnerMonster->GetStronghold()->GetWarningVolume();
			if (!WarningVolume->IsOverlappingActor(MainHero))
			{
				Blackboard->SetValueAsBool(BlackboardKey_HasTarget, false);
				Blackboard->ClearValue(BlackboardKey_Target);

				//隐藏雪条
				OwnerMonster->SetWidgetVisible(false);
			}
		}
		else
		{
			//检测英雄是否进入视野范围
			if (FVector::DistSquaredXY(OwnerMonster->GetActorLocation(), MainHero->GetActorLocation()) <= FMath::Square(MonsterConfig->SightRadius))
			{
				Blackboard->SetValueAsBool(BlackboardKey_HasTarget, true);
				Blackboard->SetValueAsObject(BlackboardKey_Target, MainHero);

				//显示血条
				OwnerMonster->SetWidgetVisible(true);
			}
		}
	}
}

FVector AMonsterController::GetPatrolRandomPosition()
{
	if (const auto* Stronghold = OwnerMonster->GetStronghold())
	{
		//获取普通小怪出生区域内的随机位置
		const auto RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(BirthPosition, FVector(50, 50, 0));
		
		//将上一步的随机位置映射到NavMesh上的位置
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (FNavLocation ProjectedLocation; NavSystem->ProjectPointToNavigation(RandomPoint, ProjectedLocation))
		{
			return ProjectedLocation.Location;
		}
	}
	return OwnerMonster->GetActorLocation();
}

AExploreCharacter* AMonsterController::GetTarget() const
{
	auto* Target = Blackboard->GetValueAsObject(BlackboardKey_Target);
	return Cast<AExploreCharacter>(Target);
}

EBTNodeResult::Type AMonsterController::ReleaseSkill()
{
	if (!Blackboard->GetValueAsBool(BlackboardKey_HasTarget))
	{
		return EBTNodeResult::Failed;
	}

	//选择要释放的技能
	auto* SkillManager = OwnerMonster->GetSkillManager();
	SkillManager->SetCurrentSkill(SkillManager->PickValidPassiveSkill());

	//向技能目标移动 bStopOnOverlap设置成True，否则当目标或者自己没有碰撞时，移动失效
	MoveToActor(Cast<AExploreCharacter>(Blackboard->GetValueAsObject(BlackboardKey_Target)), 1.0f, false);
	
	return EBTNodeResult::Type::InProgress;
}

void AMonsterController::Die()
{
	OwnerMonster->Die();
}

void AMonsterController::Revive()
{
	Blackboard->ClearValue(BlackboardKey_HasTarget);
	Blackboard->ClearValue(BlackboardKey_HasTarget);
	
	OwnerMonster->SetActorLocation(BirthPosition);
	OwnerMonster->Revive();
}
