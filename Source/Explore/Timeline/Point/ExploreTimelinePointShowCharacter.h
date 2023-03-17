// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExploreTimelinePoint.h"
#include "ExploreTimelinePointShowCharacter.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UExploreTimelinePointShowCharacter : public UExploreTimelinePoint
{
	GENERATED_BODY()

public:
	/**
	 * @brief 执行Point
	 * @param Timeline 执行此Point的Timeline
	 */
	virtual void Execute(UExploreTimeline* Timeline) override;
};
