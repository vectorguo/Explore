// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBuffBase.h"
#include "CharacterBuff_AddBuffToTargetBeforeAtk.generated.h"

/**
 * 攻击前给目标添加指定Buff的Buff
 */
UCLASS()
class EXPLORE_API UCharacterBuff_AddBuffToTargetBeforeAtk : public UCharacterBuffBase
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
	 * @brief 攻击前生效的buff
	 * @param Target 目标
	 */
	virtual void TakeEffectBeforeAtk(AExploreCharacter* Target) override;
protected:
	/**
	 * @brief 攻击目标时要给目标添加的buff
	 */
	TArray<int32> BuffTIDs;
};
