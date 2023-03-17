// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreTimeline.h"
#include "ExploreTimelineTemplate.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Table/TableString.h"
#include "Explore/Table/TableTimeline.h"
#include "Point/ExploreTimelinePoint.h"

void UExploreTimeline::Initialize(int32 InGuid, int32 InTid, const UExploreTimelineTemplate* InTemplate, float InPlayRate)
{
	Guid = InGuid;
	Tid = InTid;
	Template = InTemplate;
	PlayRate = InPlayRate;
}

void UExploreTimeline::Start()
{
	Duration = 0;
	NextPointIndex = 0;
	State = ETimelineState::ETS_Running;
}

void UExploreTimeline::Tick(float DeltaTime)
{
	Duration += DeltaTime * PlayRate;
	const auto CurrentFrame = static_cast<int32>(Duration * 30.0f);
	while (true)
	{
		if (!Template->Points.IsValidIndex(NextPointIndex))
		{
			Stop(true);
			break;
		}

		auto* NextPoint = Template->Points[NextPointIndex];
		if (CurrentFrame >= NextPoint->GetFrame())
		{
			NextPoint->Execute(this);
			++NextPointIndex;
		}
		else
		{
			break;
		}
	}
}

void UExploreTimeline::Pause()
{
	State = ETimelineState::ETS_Paused;
}

void UExploreTimeline::Resume()
{
	State = ETimelineState::ETS_Running;
}

void UExploreTimeline::Stop(bool bNormal)
{
	if (State == ETimelineState::ETS_Destroyed)
	{
		return;
	}
	State = ETimelineState::ETS_Destroyed;

	//删除特效
	for (auto& Pair : EffectsMap)
	{
		auto* Effect = Pair.Value;
		if (Effect)
		{
			if (Character)
			{
				Character->DetachEffect(Effect);
			}
			Effect->Destroy();
		}
	}
	EffectsMap.Empty();

	//触发结束回调
	if (TimelineFinishDelegate.IsBound())
	{
		TimelineFinishDelegate.Execute(bNormal ? 0 : 1);	
	}
}

AActor* UExploreTimeline::GetEffect(int32 Index)
{
	if (const auto* Pointer = EffectsMap.Find(Index))
	{
		return *Pointer;
	}

	const auto* TimelineConfig = FTableTimeline::GetRow(Tid);
	if (TimelineConfig->Effects.IsValidIndex(Index))
	{
		const auto EffectPath = FTableString::GetRow(TimelineConfig->Effects[Index])->Content;
		if (UObject* EffectObj = StaticLoadObject(UBlueprint::StaticClass(), nullptr, *EffectPath))  
		{
			const auto* EffectBP = Cast<UBlueprint>(EffectObj);
			auto* Effect = GWorld->GetWorld()->SpawnActor<AActor>(EffectBP->GeneratedClass, FVector::ZeroVector, FRotator::ZeroRotator);
			EffectsMap.Emplace(Index, Effect);
			return Effect;
		}
	}
	return nullptr;
}
