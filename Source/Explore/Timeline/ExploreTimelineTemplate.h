// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ExploreTimelineTemplate.generated.h"

class UExploreTimelinePoint;

/**
 * Timeline模板
 */
UCLASS()
class EXPLORE_API UExploreTimelineTemplate : public UObject
{
	GENERATED_BODY()

	friend class UExploreTimeline;

public:
	/**
	 * @brief 初始化
	 * @param InTid 配置表ID
	 */
	void Initialize(int32 InTid);

private:
	/**
	 * @brief 创建Point
	 * @param PointType Point类型
	 * @return Point
	 */
	UExploreTimelinePoint* CreateTimelinePoint(int32 PointType);
	
protected:
	/**
	 * @brief 所有的Points
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Timeline")
	TArray<UExploreTimelinePoint*> Points;
};
