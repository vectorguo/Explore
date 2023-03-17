// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBuffBase.h"
#include "CharacterBuff_Thunder3000.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UCharacterBuff_Thunder3000 : public UCharacterBuffBase
{
	GENERATED_BODY()

public:
	/**
	 * @brief 初始化
	 * @param ID Buff的唯一ID
	 * @param BuffOwner
	 * @param BuffCauser
	 * @param BuffConfig 技能配置
	 */
	virtual void Initialize(int32 ID, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser, const FTableBuffRowData* BuffConfig) override;

	/**
	 * @brief 更新
	 * @param DeltaTime 更新时间
	 */
	virtual void Tick(float DeltaTime) override;

protected:
	/**
	 * @brief 血量回复的间隔时间
	 */
	float IntervalTime;

	/**
	 * @brief 目标搜索范围
	 */
	float SearchingRange;

	/**
	 * @brief 目标数量
	 */
	int32 TargetCount;

	/**
	 * @brief 力量折算系数
	 */
	float StrengthRatio;

	/**
	 * @brief 敏捷折算系数
	 */
	float AgilityRatio;

	/**
	 * @brief 智力折算系数
	 */
	float IntelligenceRatio;

	/**
	 * @brief 属性类型
	 */
	ECharacterElement ElementType;

	/**
	 * @brief 当前的间隔时间
	 */
	float CurrentIntervalTime;
};
