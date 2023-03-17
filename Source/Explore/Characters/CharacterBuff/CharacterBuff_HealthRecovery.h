// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBuffBase.h"
#include "CharacterBuff_HealthRecovery.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UCharacterBuff_HealthRecovery : public UCharacterBuffBase
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
	float RecoveryIntervalTime;

	/**
	 * @brief 血量回复值
	 */
	float RecoveryValue;

	/**
	 * @brief 当前的间隔时间
	 */
	float CurrentIntervalTime;

	/**
	 * @brief 是否恢复血量百分比
	 */
	bool bIsPercent;
};
