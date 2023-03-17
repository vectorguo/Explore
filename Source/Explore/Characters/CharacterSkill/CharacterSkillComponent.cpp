// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSkillComponent.h"

#include "HeroSkillCommonAttack.h"
#include "HeroSkillSprint.h"
#include "HeroSkillSprintAttack.h"
#include "MonsterSkillCommonAttack.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Table/TableSkill.h"


// Sets default values for this component's properties
UCharacterSkillComponent::UCharacterSkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//
	Owner = Cast<AExploreCharacter>(GetOwner());
}

// Called every frame
void UCharacterSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//更新当前技能
	if (CurrentSkill)
	{
		if (CurrentSkill->GetSkillState() == ECharacterSkillState::ECSS_Finished)
		{
			CurrentSkill = nullptr;
		}
		else
		{
			CurrentSkill->Tick(DeltaTime);	
		}
	}
}

void UCharacterSkillComponent::AddSkill(int32 SkillID, bool bNeedSort)
{
	const auto* SkillConfig = FTableSkill::GetRow(SkillID);
	if (SkillConfig)
	{
		//检查技能是否已经存在
		if (SkillConfig->Type == 0)
		{
			//被动技能
			if (PassiveSkills.ContainsByPredicate([SkillID](const UCharacterSkillBase* A) { return A->GetSkillID() == SkillID; }))
			{
				return;
			}
		}
		else
		{
			//主动技能
			if (ActiveSkills.ContainsByPredicate([SkillID](const UCharacterSkillBase* A){ return A->GetSkillID() == SkillID; }))
			{
				return;
			}
		}
		
		UCharacterSkillBase* Skill;
		switch (SkillConfig->Kind)
		{
		case 1:
			//英雄普通攻击技能
			Skill = NewObject<UHeroSkillCommonAttack>(this);
			break;
		case 2:
			//英雄冲刺攻击技能
			Skill = NewObject<UHeroSkillSprintAttack>(this);
			break;
		case 3:
			//英雄冲刺
			Skill = NewObject<UHeroSkillSprint>(this);
			break;
		case 101:
			//怪物普通攻击技能
			Skill = NewObject<UMonsterSkillCommonAttack>(this);
			break;
		default:
			Skill = nullptr;
		}

		if (Skill)
		{
			Skill->Initialize(Owner, SkillConfig);
			if (Skill->GetSkillType() == ECharacterSkillType::ECST_Active)
			{
				ActiveSkills.Add(Skill);
				if (bNeedSort)
				{
					ActiveSkills.Sort([](const UCharacterSkillBase& A, const UCharacterSkillBase& B) {
						return A.GetSkillPriority() > B.GetSkillPriority();
					});
				}
			}
			else
			{
				PassiveSkills.Add(Skill);
				if (bNeedSort)
				{
					PassiveSkills.Sort([](const UCharacterSkillBase& A, const UCharacterSkillBase& B) {
						return A.GetSkillPriority() > B.GetSkillPriority();
					});
				}
			}
		}
	}
}

void UCharacterSkillComponent::RemoveSkill(uint32 SkillID)
{
	const auto Index = PassiveSkills.IndexOfByPredicate([SkillID] (const UCharacterSkillBase* Skill)
	{
		return Skill->GetSkillID() == SkillID;
	});
	if (Index != INDEX_NONE)
	{
		delete PassiveSkills[Index];
		PassiveSkills.RemoveAt(Index);
	}
}

UCharacterSkillBase* UCharacterSkillComponent::GetActiveSkill(int32 SkillID) const
{
	for (auto* Skill : ActiveSkills)
	{
		if (Skill->GetSkillID() == SkillID)
		{
			return Skill;
		}
	}
	return nullptr;
}

UCharacterSkillBase* UCharacterSkillComponent::GetPassiveSkill(int32 SkillID) const
{
	for (auto* Skill : PassiveSkills)
	{
		if (Skill->GetSkillID() == SkillID)
		{
			return Skill;
		}
	}
	return nullptr;
}

UCharacterSkillBase* UCharacterSkillComponent::PickValidPassiveSkill()
{
	auto Priority = 10000000;
	auto RandomValue = 0;
	
	for (auto Iter = PassiveSkills.CreateIterator(); Iter; ++Iter)
	{
		auto* Skill = *Iter;
		if (Skill->IsValid())
		{
			//概率随机
			if (Priority != Skill->GetSkillPriority())
			{
				Priority = Skill->GetSkillPriority();
				RandomValue = FMath::RandRange(0, 100);
			}
			RandomValue -= Skill->GetSkillProbability();
			if (RandomValue <= 0)
			{
				Skill->SetSkillState(ECharacterSkillState::ECSS_Ready);
				return Skill;
			}
		}
	}
	return nullptr;
}

bool UCharacterSkillComponent::ReleaseValidPassiveSkill()
{
	if (auto* Skill = PickValidPassiveSkill())
	{
		CurrentSkill = Skill;
		CurrentSkill->Release();
		return true;
	}
	return false;
}
