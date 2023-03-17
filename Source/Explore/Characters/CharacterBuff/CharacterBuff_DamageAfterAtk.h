// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBuffBase.h"
#include "CharacterBuff_DamageAfterAtk.generated.h"

/**
 * 攻击前给目标添加指定Buff的Buff
 */
UCLASS()
class EXPLORE_API UCharacterBuff_DamageAfterAtk : public UCharacterBuffBase
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
	 * @brief 攻击后生效的buff
	 * @param MainTarget 目标
	 */
	virtual void TakeEffectAfterAtk(AExploreCharacter* MainTarget) override;
	
protected:
	/**
	 * @brief 释放概率
	 */
	float Probability;
	
	/**
	 * @brief 伤害范围，如果伤害范围是-1，则代表是单体伤害
	 */
	float DamageRange;

	/**
	 * @brief 伤害类型,1代表属性伤害，2代表纯粹伤害
	 */
	int32 DamageType;

	/**
	 * @brief 伤害参数1（如果伤害类型是1，则代表力量系数，如果伤害类型是2，则代表是攻击力系数）
	 */
	float DamageParam1;

	/**
	 * @brief 伤害参数2（如果伤害类型是1，则代表敏捷系数）
	 */
	float DamageParam2;

	/**
	 * @brief 伤害参数3（如果伤害类型是1，则代表智力系数）
	 */
	float DamageParam3;

	/**
	 * @brief 伤害参数4（如果伤害类型是1，则代表属性）
	 */
	float DamageParam4;

	/**
	 * @brief 伤害表现Tid
	 */
	int32 TimelineTid;
};
