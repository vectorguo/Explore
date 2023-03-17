// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExploreTimelinePoint.h"
#include "ExploreTimelinePointEffect.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UExploreTimelinePointEffect : public UExploreTimelinePoint
{
	GENERATED_BODY()

public:
	/**
	 * @brief 初始化Point
	 * @param Params 参数列表
	 * @param Index 参数起始索引
	 */
	virtual void Initialize(const TArray<float>& Params, int32& Index) override;
	
	/**
	 * @brief 执行Point
	 * @param Timeline 执行此Point的Timeline
	 */
	virtual void Execute(UExploreTimeline* Timeline) override;
	
protected:
	/**
	 * @brief 动画名称
	 */
	int32 EffectIndex;
	
	/**
	 * @brief 是否挂到角色身上
	 */
	bool bAttachToCharacter;

	/**
	 * @brief 特效挂载的Socket名称
	 */
	FString AttachSocket;
};
