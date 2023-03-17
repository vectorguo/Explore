// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreTimelinePointDamage.h"

#include "Explore/Characters/CharacterBuff/CharacterBuffBase.h"
#include "Explore/Characters/CharacterSkill/CharacterSkillBase.h"
#include "Explore/Timeline/ExploreTimeline.h"


void UExploreTimelinePointDamage::Initialize(const TArray<float>& Params, int32& Index)
{
	Super::Initialize(Params, Index);

	//是否是技能伤害
	bIsSkillDamage = Params[Index++] == 1;
}

void UExploreTimelinePointDamage::Execute(UExploreTimeline* Timeline)
{
	Super::Execute(Timeline);
	
	//伤害计算
	if (bIsSkillDamage)
	{
		if (auto* Skill = Timeline->GetSkill())
		{
			Skill->ApplyDamage();
		}	
	}
	else
	{
		if (auto* Buff = Timeline->GetBuff())
		{
			Buff->ApplyDamage();
		}
	}
}
