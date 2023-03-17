// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreTimelinePointEffect.h"

#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Table/TableString.h"
#include "Explore/Timeline/ExploreTimeline.h"

void UExploreTimelinePointEffect::Initialize(const TArray<float>& Params, int32& Index)
{
	Super::Initialize(Params, Index);

	//特效索引
	EffectIndex = Params[Index++];

	//挂点名称
	int32 Value = Params[Index++];
	bAttachToCharacter = Value > 0;
	if (bAttachToCharacter)
	{
		AttachSocket = FTableString::GetRow(Value)->Content;	
	}
}

void UExploreTimelinePointEffect::Execute(UExploreTimeline* Timeline)
{
	Super::Execute(Timeline);

	if (auto* Character = Timeline->GetCharacter())
	{
		if (auto* Effect = Timeline->GetEffect(EffectIndex))
		{
			if (bAttachToCharacter)
			{
				Character->AttachEffect(Effect, FName(AttachSocket), true);
			}
			else
			{
				Effect->SetActorLocation(Character->GetActorLocation());
			}
		}
	}
}
