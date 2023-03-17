// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBuff_Thunder3000.h"

#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/Monster/MonsterBase.h"
#include "Explore/Timeline/ExploreTimelineManager.h"
#include "Explore/Utility/ExploreUtility.h"
#include "Kismet/GameplayStatics.h"

void UCharacterBuff_Thunder3000::Initialize(int32 ID, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser, const FTableBuffRowData* BuffConfig)
{
	Super::Initialize(ID, BuffOwner, BuffCauser, BuffConfig);
	
	if (BuffConfig->Params.Num() >= 6)
	{
		IntervalTime		= BuffConfig->Params[0];
		SearchingRange		= BuffConfig->Params[1];
		TargetCount			= BuffConfig->Params[2];
		StrengthRatio		= BuffConfig->Params[3];
		AgilityRatio		= BuffConfig->Params[4];
		IntelligenceRatio	= BuffConfig->Params[5];
		ElementType			= static_cast<ECharacterElement>(BuffConfig->Params[6]);
	}
}

void UCharacterBuff_Thunder3000::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BuffState == EBuffState::EBS_Finished)
	{
		return;
	}

	CurrentIntervalTime += DeltaTime;
	if (CurrentIntervalTime < IntervalTime)
	{
		return;
	}

	//更新时间
	CurrentIntervalTime -= IntervalTime;

	//选择目标并计算伤害
	auto* CauserAttribute = Owner->GetAttribute();
	auto Targets = FExploreUtility::FindRandomMonster(Causer->GetActorLocation(), SearchingRange, TargetCount);
	for (auto* Target : Targets)
	{
		const auto* TargetAttribute = Target->GetAttribute();
		
		//计算属性伤害
		auto DamageValue = FExploreUtility::CalculateAttributeDamage(CauserAttribute, StrengthRatio, AgilityRatio, IntelligenceRatio, ElementType);
		DamageValue = FExploreUtility::CalculateFinalDamage(DamageValue, CauserAttribute, TargetAttribute);
		if (DamageValue >= 1.0f)
		{
			UGameplayStatics::ApplyDamage(Target, -DamageValue, Owner->GetController(), Owner, Owner->GetDamageType());
		}

		//播放伤害表现
		auto* TimelineManager = UExploreGameManager::GetInstance()->GetTimelineManager();
		TimelineManager->PlayTimeline(3002, 1.0f, Target, this);
	}
}
