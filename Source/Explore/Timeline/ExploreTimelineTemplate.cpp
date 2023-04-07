// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreTimelineTemplate.h"

#include "Explore/Table/TableTimeline.h"
#include "Point/ExploreTimelinePoint.h"
#include "Point/ExploreTimelinePointAnimation.h"
#include "Point/ExploreTimelinePointArmWeaponFacade.h"
#include "Point/ExploreTimelinePointDamage.h"
#include "Point/ExploreTimelinePointEffect.h"
#include "Point/ExploreTimelinePointEmpty.h"
#include "Point/ExploreTimelinePointHideCharacter.h"
#include "Point/ExploreTimelinePointShowCharacter.h"

void UExploreTimelineTemplate::Initialize(int32 InTid)
{
	const auto* TimelineConfig = FTableTimeline::GetRow(InTid);
	for (auto Index = 0; Index < TimelineConfig->Params.Num();)
	{
		if (auto* Point = CreateTimelinePoint(TimelineConfig->Params[Index++]))
		{
			Point->Initialize(TimelineConfig->Params, Index);
			Points.Emplace(Point);
		}
	}
}

UExploreTimelinePoint* UExploreTimelineTemplate::CreateTimelinePoint(int32 PointType)
{
	switch (PointType)
	{
		case 0:
			return NewObject<UExploreTimelinePointEmpty>(this);
		case 1:
			return NewObject<UExploreTimelinePointAnimation>(this);
		case 2:
			return NewObject<UExploreTimelinePointDamage>(this);
		case 3:
			return NewObject<UExploreTimelinePointEffect>(this);
		case 11:
			return NewObject<UExploreTimelinePointShowCharacter>(this);
		case 12:
			return NewObject<UExploreTimelinePointHideCharacter>(this);
		case 13:
			return NewObject<UExploreTimelinePointArmWeaponFacade>(this);
		default:
			return nullptr;
	}
}
