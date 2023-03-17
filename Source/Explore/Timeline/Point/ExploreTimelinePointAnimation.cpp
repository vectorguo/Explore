// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreTimelinePointAnimation.h"

#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Table/TableString.h"
#include "Explore/Timeline/ExploreTimeline.h"

void UExploreTimelinePointAnimation::Initialize(const TArray<float>& Params, int32& Index)
{
	Super::Initialize(Params, Index);

	AnimationName = FName(FTableString::GetRow(Params[Index++])->Content);
	PlayRate = Params[Index++];
}

void UExploreTimelinePointAnimation::Execute(UExploreTimeline* Timeline)
{
	Super::Execute(Timeline);

	if (auto* Character = Timeline->GetCharacter())
	{
		Character->PlayMontage(AnimationName, PlayRate * Timeline->GetPlayRate());
	}
}
