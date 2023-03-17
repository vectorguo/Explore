// Fill out your copyright notice in the Description page of Project Settings.

#include "ExploreTimelineManager.h"
#include "ExploreTimeline.h"
#include "ExploreTimelineTemplate.h"

void UExploreTimelineManager::Tick(float DeltaTime)
{
	if (!NewTimelines.IsEmpty())
	{
		for (auto* Timeline : NewTimelines)
		{
			Timelines.Emplace(Timeline->GetGuid(), Timeline);
		}
		NewTimelines.Empty();
	}
	
	for (auto Iter = Timelines.CreateIterator(); Iter; ++Iter)
	{
		auto* Timeline = Iter->Value;
		if (Timeline->GetState() == ETimelineState::ETS_Running)
		{
			Timeline->Tick(DeltaTime);
		}

		if (Timeline->GetState() == ETimelineState::ETS_Destroyed)
		{
			Iter.RemoveCurrent();
		}
	}
}

int32 UExploreTimelineManager::PlayTimeline(int32 InTid, float InPlayRate, AExploreCharacter* InCharacter)
{
	auto* Timeline = CreateTimeline(InTid, InPlayRate, InCharacter);
	Timeline->Start();
	return Timeline->GetGuid();
}

int32 UExploreTimelineManager::PlayTimeline(int32 InTid, float InPlayRate, AExploreCharacter* InCharacter, UCharacterSkillBase* Skill)
{
	auto* Timeline = CreateTimeline(InTid, InPlayRate, InCharacter);
	Timeline->SetSkill(Skill);
	Timeline->Start();
	return Timeline->GetGuid();
}

int32 UExploreTimelineManager::PlayTimeline(int32 InTid, float InPlayRate, AExploreCharacter* InCharacter, UCharacterBuffBase* Buff)
{
	auto* Timeline = CreateTimeline(InTid, InPlayRate, InCharacter);
	Timeline->SetBuff(Buff);
	Timeline->Start();
	return Timeline->GetGuid();
}

void UExploreTimelineManager::PauseTimeline(int32 InGuid)
{
	if (auto* Timeline = GetTimeline(InGuid))
	{
		Timeline->Pause();	
	}
}

void UExploreTimelineManager::ResumeTimeline(int32 InGuid)
{
	if (auto* Timeline = GetTimeline(InGuid))
	{
		Timeline->Resume();	
	}
}

void UExploreTimelineManager::StopTimeline(int32 InGuid)
{
	if (auto* Timeline = GetTimeline(InGuid))
	{
		Timeline->Stop();	
	}
}

UExploreTimeline* UExploreTimelineManager::CreateTimeline(int32 InTid, float PlayRate, AExploreCharacter* InCharacter)
{
	//获取Template
	const UExploreTimelineTemplate* Template;
	if (auto* Pointer = Templates.Find(InTid))
	{
		Template = *Pointer;
	}
	else
	{
		auto* TemplateObj = NewObject<UExploreTimelineTemplate>(this);
		TemplateObj->Initialize(InTid);
		Template = TemplateObj;
		Templates.Emplace(InTid, Template);
	}

	//创建Timeline
	static int32 Guid = 0;
	auto* Timeline = NewObject<UExploreTimeline>(this);
	Timeline->Initialize(++Guid, InTid, Template, PlayRate);
	Timeline->SetCharacter(InCharacter);
	NewTimelines.Emplace(Timeline);
	return Timeline;
}

UExploreTimeline* UExploreTimelineManager::GetTimeline(int32 InGuid)
{
	auto* Pointer = Timelines.Find(InGuid);
	if (Pointer)
	{
		return *Pointer;
	}

	Pointer = NewTimelines.FindByPredicate([InGuid](const UExploreTimeline* Timeline)
	{
		return Timeline->GetGuid() == InGuid;
	});
	return Pointer ? *Pointer : nullptr;
}
