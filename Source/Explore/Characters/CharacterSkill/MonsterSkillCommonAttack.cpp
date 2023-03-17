#include "MonsterSkillCommonAttack.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/Monster/MonsterBase.h"
#include "Explore/Characters/Monster/MonsterController.h"
#include "Kismet/KismetMathLibrary.h"

void UMonsterSkillCommonAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotateToTarget)
	{
		auto* Monster = Cast<AMonsterBase>(Owner);
		auto* MonsterController = Monster->GetController<AMonsterController>();
		const auto* Target = MonsterController->GetTarget();
		if (Target)
		{
			const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Monster->GetActorLocation(), Target->GetActorLocation());
			const FRotator LookAtYaw(0, LookAtRotation.Yaw, 0);
			FRotator InterpRotation = FMath::RInterpTo(Monster->GetActorRotation(), LookAtYaw, DeltaTime, 15.0f);
			Monster->SetActorRotation(InterpRotation);
			
			// if (FMath::Abs(InterpRotation.Yaw - LookAtYaw.Yaw) <= 0.5f)
			// {
			// 	bRotateToTarget = false;
			// }
		}
	}
}

void UMonsterSkillCommonAttack::Release()
{
	Super::Release();

	//是否需要转向目标
	bRotateToTarget = NeedRotateToTarget();
	
	//播放技能动作
	PlayTimeline();
}

AExploreCharacter* UMonsterSkillCommonAttack::GetMainTarget() const
{
	const auto* MonsterController = Owner->GetController<AMonsterController>();
	auto* Target = MonsterController->GetTarget();
	if (Target)
	{
		//检测距离是否在攻击范围内
		if (FVector::DistSquaredXY(Target->GetActorLocation(), Owner->GetActorLocation()) > GetReleasingRangeSquared() * 1.1f)
		{
			Target = nullptr;
		}
	}
	
	return Target;
}
