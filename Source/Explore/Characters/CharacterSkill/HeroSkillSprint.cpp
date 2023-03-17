#include "HeroSkillSprint.h"

#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Table/TableSkill.h"

void UHeroSkillSprint::Initialize(AExploreCharacter* Character, const FTableSkillRowData* InSkillConfig)
{
	Super::Initialize(Character, InSkillConfig);

	bUnlock = false;
	SprintSpeed = InSkillConfig->SearchingRange;
}

bool UHeroSkillSprint::IsValid()
{
	if (Owner->GetWorld()->GetTimeSeconds() - LastSkillReleaseTime <= CD)
	{
		return false;
	}
	return true;
}

void UHeroSkillSprint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//更新冲刺位置
	Owner->SetActorLocation(Owner->GetActorLocation() + SprintDirection * SprintSpeed * DeltaTime);
}

void UHeroSkillSprint::Release()
{
	Super::Release();
	
	//播放技能表现
	PlayTimeline();
}