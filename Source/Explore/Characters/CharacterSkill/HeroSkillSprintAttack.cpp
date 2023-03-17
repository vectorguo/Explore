#include "HeroSkillSprintAttack.h"

#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/Hero/MainHeroBlackboard.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Monster/MonsterBase.h"
#include "Explore/Table/TableSkill.h"
#include "Explore/Utility/ExploreUtility.h"

void UHeroSkillSprintAttack::Initialize(AExploreCharacter* Character, const FTableSkillRowData* InSkillConfig)
{
	Super::Initialize(Character, InSkillConfig);

	SprintSpeed = InSkillConfig->SearchingRange;
}

bool UHeroSkillSprintAttack::IsValid()
{
	//查找技能目标
	const auto* Hero = Cast<AMainHero>(Owner);
	TargetCache = FExploreUtility::FindNearestMonsterInStronghold(Hero, Hero->GetBlackboard()->GetMonsterStronghold(), GetSearchingRange());
	if (TargetCache == nullptr)
	{
		//没找到目标，不能释放技能
		return false;
	}
	
	//找到目标，检测目标距离是否符合技能释放条件
	auto Delta = TargetCache->GetActorLocation() - Hero->GetActorLocation();
	Delta.Z = 0;
	if (Delta.SquaredLength() <= GetReleasingRangeSquared())
	{
		//目标距离太近，无法释放冲刺技能
		TargetCache = nullptr;
		return false;
	}
	
	//可以释放技能，计算冲刺参数
	Delta.Normalize();
	SprintTime = (GetSearchingRange() - GetReleasingRange()) / SprintSpeed;
	SprintDirection = Delta;
	return true;
}

void UHeroSkillSprintAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//向目标移动，移动到攻击距离停止
	if (SprintTime > 0)
	{
		Owner->SetActorLocation(Owner->GetActorLocation() + SprintDirection * SprintSpeed * DeltaTime);

		//检测与目标的距离是否到达技能释放范围，如果到了就停止冲刺
		if (TargetCache && (FVector::DistSquaredXY(Owner->GetActorLocation(), TargetCache->GetActorLocation()) <= GetReleasingRangeSquared()))
		{
			SprintTime = -1.0f;
		}
		else
		{
			SprintTime -= DeltaTime;
		}
	}
}

void UHeroSkillSprintAttack::Release()
{
	Super::Release();

	//记录技能目标
	const auto* Hero = Cast<AMainHero>(Owner);
	Hero->GetBlackboard()->SetSkillTarget(TargetCache);
	
	//播放技能表现
	PlayTimeline();
}

void UHeroSkillSprintAttack::Stop()
{
	Super::Stop();

	//清空缓存目标
	TargetCache = nullptr;
	
	//停止播放技能动作
	Owner->StopMontage(0.3f);
}
