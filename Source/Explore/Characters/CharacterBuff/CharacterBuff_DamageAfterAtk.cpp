// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBuff_DamageAfterAtk.h"

#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/Monster/MonsterBase.h"
#include "Explore/Timeline/ExploreTimelineManager.h"
#include "Explore/Utility/ExploreUtility.h"
#include "Kismet/GameplayStatics.h"

void UCharacterBuff_DamageAfterAtk::Initialize(int32 ID, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser, const FTableBuffRowData* BuffConfig)
{
	Super::Initialize(ID, BuffOwner, BuffCauser, BuffConfig);

	Probability = BuffConfig->Params[0];
	DamageRange = BuffConfig->Params[1];
	TimelineTid = BuffConfig->Params[2];
	DamageType = BuffConfig->Params[3];
	if (DamageType == 1)
	{
		//属性伤害
		DamageParam1 = BuffConfig->Params[4];
		DamageParam2 = BuffConfig->Params[5];
		DamageParam3 = BuffConfig->Params[6];
		DamageParam4 = BuffConfig->Params[7];
	}
	else if (DamageType == 2)
	{
		//纯粹伤害
		DamageParam1 = BuffConfig->Params[4];
	}
}

void UCharacterBuff_DamageAfterAtk::TakeEffectAfterAtk(AExploreCharacter* MainTarget)
{
	Super::TakeEffectBeforeAtk(MainTarget);

	if (MainTarget == nullptr)
	{
		return;
	}

	const auto RandomValue = FMath::RandRange(0.0f, 100.0f);
	if (RandomValue > Probability)
	{
		return;
	}

	//播放伤害表现
	if (TimelineTid > 0)
	{
		auto* TimelineManager = UExploreGameManager::GetInstance()->GetTimelineManager();
		TimelineManager->PlayTimeline(TimelineTid, 1.0f, MainTarget, this);	
	}

	//计算伤害
	const auto* CauserAttribute = Owner->GetAttribute();
	auto DamageValue = DamageType == 1 ?
		FExploreUtility::CalculateAttributeDamage(CauserAttribute, DamageParam1, DamageParam2, DamageParam3, static_cast<ECharacterElement>(DamageParam4)) :
		CauserAttribute->GetAttackValue() * DamageParam1;
	
	if (DamageRange < 0)
	{
		//单体伤害
		const auto* TargetAttribute = MainTarget->GetAttribute();
		DamageValue = FExploreUtility::CalculateFinalDamage(DamageValue, CauserAttribute, TargetAttribute);
		if (DamageValue >= 1.0f)
		{
			UGameplayStatics::ApplyDamage(MainTarget, -DamageValue, Owner->GetController(), Owner, Owner->GetDamageType());
		}
	}
	else
	{
		//群体伤害
		auto Targets = FExploreUtility::FindRandomMonster(Causer->GetActorLocation(), DamageRange, -1);
		for (auto* Target : Targets)
		{
			const auto* TargetAttribute = Target->GetAttribute();
			DamageValue = FExploreUtility::CalculateFinalDamage(DamageValue, CauserAttribute, TargetAttribute);
			if (DamageValue >= 1.0f)
			{
				UGameplayStatics::ApplyDamage(Target, -DamageValue, Owner->GetController(), Owner, Owner->GetDamageType());
			}
		}
	}
}