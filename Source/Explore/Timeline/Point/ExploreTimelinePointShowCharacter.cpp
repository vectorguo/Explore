// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreTimelinePointShowCharacter.h"

#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Timeline/ExploreTimeline.h"

void UExploreTimelinePointShowCharacter::Execute(UExploreTimeline* Timeline)
{
	Super::Execute(Timeline);

	if (auto* Character = Timeline->GetCharacter())
	{
		Character->SetVisible(true);
	}
}
