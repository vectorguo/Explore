#include "HeroSkillCommonAttack.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/Hero/MainHeroBlackboard.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Monster/MonsterBase.h"
#include "Explore/Utility/ExploreUtility.h"
#include "Kismet/KismetMathLibrary.h"

void UHeroSkillCommonAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMoveToTarget)
	{
		auto* Hero = Cast<AMainHero>(Owner);
		if (const auto* Target = Hero->GetBlackboard()->GetSkillTarget())
		{
			if (FVector::DistSquaredXY(Target->GetActorLocation(), Hero->GetActorLocation()) <= GetReleasingRangeSquared())
			{
				//达到施法距离，播放技能表现
				bMoveToTarget = false;
				bRotateToTarget = NeedRotateToTarget();

				//停止移动
				Hero->GetController()->StopMovement();
				
				//播放技能表现
				PlayTimeline();
			}
			else
			{
				//继续向目标移动
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(Hero->GetController(), Target->GetActorLocation());
			}
		}
		else
		{
			//目标已丢失，直接播放技能表现
			PlayTimeline();
		}
	}
	else if (bRotateToTarget)
	{
		auto* Hero = Cast<AMainHero>(Owner);
		const auto* Target = Hero->GetBlackboard()->GetSkillTarget();
		if (Target)
		{
			const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Hero->GetActorLocation(), Target->GetActorLocation());
			const FRotator LookAtYaw(0, LookAtRotation.Yaw, 0);
			FRotator InterpRotation = FMath::RInterpTo(Hero->GetActorRotation(), LookAtYaw, DeltaTime, 15.0f);
			Hero->SetActorRotation(InterpRotation);
			
			if (FMath::Abs(InterpRotation.Yaw - LookAtYaw.Yaw) <= 0.5f)
			{
				bRotateToTarget = false;
			}
		}
	}
}

void UHeroSkillCommonAttack::Release()
{
	Super::Release();
	
	bMoveToTarget = false;
	bRotateToTarget = false;
	
	//查找技能目标
	const auto* Hero = Cast<AMainHero>(Owner);
	auto* Blackboard = Hero->GetBlackboard();
	auto* Target = FExploreUtility::FindNearestMonsterInStronghold(Hero, Blackboard->GetMonsterStronghold(), GetSearchingRange());
	Blackboard->SetSkillTarget(Target);

	//检测目标与英雄之间的距离，如果超出技能释放距离，就移动到目标身边再释放技能
	if (Target)
	{
		if (FVector::DistSquaredXY(Target->GetActorLocation(), Hero->GetActorLocation()) <= GetReleasingRangeSquared())
		{
			//英雄与目标之间的距离小于技能的释放范围，直接释放技能
			PlayTimeline();

			//检测是否需要转向
			if (NeedRotateToTarget())
			{
				bRotateToTarget = true;
			}
		}
		else
		{
			//英雄与目标之间的距离大于技能的释放范围，向目标移动
			bMoveToTarget = true;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(Hero->GetController(), Target->GetActorLocation());
		}
	}
	else
	{
		//播放技能动作
		PlayTimeline();
	}
}

AExploreCharacter* UHeroSkillCommonAttack::GetMainTarget() const
{
	const auto* Hero = Cast<AMainHero>(Owner);
	return Hero->GetBlackboard()->GetSkillTarget();
}
