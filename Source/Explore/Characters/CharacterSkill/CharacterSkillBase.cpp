#include "CharacterSkillBase.h"

#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/CharacterAttribute/CharacterAttribute.h"
#include "Explore/Table/TableSkill.h"
#include "Explore/Timeline/ExploreTimelineManager.h"
#include "Explore/Utility/ExploreUtility.h"
#include "Kismet/GameplayStatics.h"

void UCharacterSkillBase::Initialize(AExploreCharacter* Character, const FTableSkillRowData* InSkillConfig)
{
	Owner = Character;
	SkillConfig = InSkillConfig;
	SkillID = InSkillConfig->ID;
	SkillProbability = InSkillConfig->Probability;
	SkillElement = static_cast<ECharacterElement>(InSkillConfig->Element);
	CD = InSkillConfig->CD;
}

void UCharacterSkillBase::Release()
{
	SetSkillState(ECharacterSkillState::ECSS_Releasing);

	//记录技能释放时间
	LastSkillReleaseTime = Owner->GetWorld()->GetTimeSeconds();
}

void UCharacterSkillBase::Stop()
{
	SetSkillState(ECharacterSkillState::ECSS_Finished);

	//停止播放Timeline
	if (TimelineGuid != -1)
	{
		auto* TimelineManager = UExploreGameManager::GetInstance()->GetTimelineManager();
		TimelineManager->StopTimeline(TimelineGuid);
		TimelineGuid = -1;
	}

	//停止播放技能动作
	Owner->StopMontage(0.3f);
}

void UCharacterSkillBase::ApplyDamage()
{
	switch (SkillConfig->DamageType)
	{
		case 1:
			//单体伤害
			ApplyDamage_SingleTarget();
		default:
			return;
	}
}

float UCharacterSkillBase::GetSkillSpeed() const
{
	return SkillConfig->DynamicSkillSpeed == 1 ? Owner->GetAttribute()->GetAttributeValue(EAttributeType::EAT_SkillSpeed) / 100.0f : 1.0f;
}

void UCharacterSkillBase::PlayTimeline()
{
	auto* TimelineManager = UExploreGameManager::GetInstance()->GetTimelineManager();
	TimelineGuid = TimelineManager->PlayTimeline(SkillConfig->Timeline, GetSkillSpeed(), Owner, this, this, &UCharacterSkillBase::OnTimelineEnd);
}

void UCharacterSkillBase::OnTimelineEnd(int32 EndContext)
{
	TimelineGuid = -1;

	//停止技能播放
	Stop();
}

void UCharacterSkillBase::ApplyDamage_SingleTarget()
{
	//有效的MainTarget
	auto* MainTarget = GetMainTarget();
	if (MainTarget == nullptr)
	{
		return;
	}

	//检测目标是否有效
	if (MainTarget->IsDead())
	{
		return;
	}

	//触发攻击方造成伤害之前的Buff效果
	Owner->GetBuffManager()->InvokeBuffBeforeAtk(MainTarget);
	
	//计算普通伤害(暴击，闪避)
	auto* CauserAttribute = Owner->GetAttribute();
	const auto* TargetAttribute = MainTarget->GetAttribute();
	auto DamageValue = FExploreUtility::CalculateNormalDamage(CauserAttribute, TargetAttribute);
	DamageValue *= GetDamageRatio();

	//计算属性加成的伤害
	DamageValue += FExploreUtility::CalculateAttributeDamage(CauserAttribute, SkillConfig->DamageParams[1], SkillConfig->DamageParams[2], SkillConfig->DamageParams[3], ECharacterElement::ECE_None);

	//计算攻击方伤害加成和目标的伤害减免和伤害抵挡
	DamageValue = FExploreUtility::CalculateFinalDamage(DamageValue, CauserAttribute, TargetAttribute);
	if (DamageValue >= 1.0f)
	{
		UGameplayStatics::ApplyDamage(MainTarget, -DamageValue, Owner->GetController(), Owner, Owner->GetDamageType());
	}
	
	//计算攻击方吸血
	CauserAttribute->ModifyHealth(DamageValue * CauserAttribute->GetAttributeValue(EAttributeType::EAT_BloodAbsorbing) / 100.0f);
	
	//触发攻击方造成伤害之后的Buff效果
	Owner->GetBuffManager()->InvokeBuffAfterAtk(MainTarget);
}
