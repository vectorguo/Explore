// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ExploreTimelinePoint.generated.h"

/**
 * Timeline事件Point
 */
UCLASS()
class EXPLORE_API UExploreTimelinePoint : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 初始化Point
	 * @param Params 参数列表
	 * @param Index 参数起始索引
	 */
	virtual void Initialize(const TArray<float>& Params, int32& Index)
	{
		Frame = Params[Index++];
	}
	
	/**
	 * @brief 执行Point
	 */
	virtual void Execute(class UExploreTimeline* Timeline)
	{
		
	}
	
	/**
	 * @brief 获取帧数
	 * @return 帧数
	 */
	FORCEINLINE int32 GetFrame() const
	{
		return Frame;
	}
	
protected:
	/**
	 * @brief 帧数
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Timeline")
	int32 Frame;
};
