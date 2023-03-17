// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainHeroBlackboard.generated.h"

class AExploreCharacter;
class AMonsterStronghold;
class ANpc;

/**
 * 英雄运行时相关数据
 */
UCLASS()
class EXPLORE_API UMainHeroBlackboard : public UObject
{
	GENERATED_BODY()

public:
	UMainHeroBlackboard();

	/**
	 * @brief 获取当前所在的怪物据点
	 * @return 怪物据点
	 */
	FORCEINLINE class AMonsterStronghold* GetMonsterStronghold() const
	{
		return MonsterStronghold;
	}

	/**
	 * @brief 设置当前所在的怪物据点
	 * @param Stronghold 怪物据点
	 */
	FORCEINLINE void SetMonsterStronghold(class AMonsterStronghold* Stronghold)
	{
		MonsterStronghold = Stronghold;
	}
	
	/**
	 * @brief 获取技能目标
	 * @return 技能目标
	 */
	FORCEINLINE AExploreCharacter* GetSkillTarget() const
	{
		return SkillTarget;
	}

	/**
	 * @brief 是否存在技能目标
	 * @return 是否存在技能目标
	 */
	FORCEINLINE bool HasSkillTarget() const
	{
		return SkillTarget != nullptr;
	}

	/**
	 * @brief 设置技能目标
	 * @param Target 技能目标
	 */
	FORCEINLINE void SetSkillTarget(AExploreCharacter* Target)
	{
		SkillTarget = Target;
	}

	/**
	 * @brief 获取可以交互的NPC
	 * @return 可以交互的NPC
	 */
	FORCEINLINE ANpc* GetInteractiveNpc() const
	{
		return InteractiveNpc;
	}

	/**
	 * @brief 是否存在可以交互的NPC
	 * @return 是否存在可以交互的NPC
	 */
	FORCEINLINE bool HasInteractiveNpc() const
	{
		return InteractiveNpc != nullptr;
	}

	/**
	 * @brief 设置可以交互的NPC
	 * @param Target 可以交互的NPC
	 */
	FORCEINLINE void SetInteractiveNpc(ANpc* Target)
	{
		InteractiveNpc = Target;
	}
	
protected:
	/**
	 * @brief 所在怪物据点
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	AMonsterStronghold* MonsterStronghold;
	
	/**
	 * @brief 技能目标
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	AExploreCharacter* SkillTarget = nullptr;

	/**
	 * @brief 最近的可交互的NPC
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	ANpc* InteractiveNpc;
};
