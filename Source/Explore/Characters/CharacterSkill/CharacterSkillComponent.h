// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterSkillBase.h"
#include "Components/ActorComponent.h"
#include "CharacterSkillComponent.generated.h"

class AExploreCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EXPLORE_API UCharacterSkillComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UCharacterSkillComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief 添加技能
	 * @param SkillID 技能ID
	 * @param bNeedSort 添加完技能是否需要对技能列表进行排序
	 */
	void AddSkill(int32 SkillID, bool bNeedSort = true);

	/**
	 * @brief 删除技能
	 * @param SkillID 要被删除的技能ID
	 */
	void RemoveSkill(uint32 SkillID);

	/**
	 * @brief 获取指定ID的主动技能
	 * @param SkillID 主动技能ID
	 * @return 主动技能
	 */
	UCharacterSkillBase* GetActiveSkill(int32 SkillID) const;
	
	/**
	 * @brief 获取指定ID的被动技能
	 * @param SkillID 被动技能ID
	 * @return 被动技能
	 */
	UCharacterSkillBase* GetPassiveSkill(int32 SkillID) const;

	/**
	 * @brief 获取可用的被动技能
	 * @return 可用的被动技能
	 */
	UCharacterSkillBase* PickValidPassiveSkill();

	/**
	 * @brief 释放可用的被动技能
	 * @return 是否释放成功
	 */
	bool ReleaseValidPassiveSkill();

	/**
	 * @brief 获取当前技能
	 * @return 当前技能
	 */
	FORCEINLINE UCharacterSkillBase* GetCurrentSkill() const
	{
		return CurrentSkill;
	}

	/**
	 * @brief 设置当前释放的技能
	 * @param Skill 正在释放的技能
	 */
	FORCEINLINE void SetCurrentSkill(UCharacterSkillBase* Skill)
	{
		CurrentSkill = Skill;
	}

	/**
	 * @brief 停止释放当前技能
	 */
	FORCEINLINE void StopCurrentSkill()
	{
		if (CurrentSkill)
		{
			CurrentSkill->Stop();
			CurrentSkill = nullptr;
		}
	}
	
protected:
	/**
	 * @brief Buff拥有者
	 */
	UPROPERTY()
	AExploreCharacter* Owner = nullptr;
	
	/**
	 * @brief 主动动技能列表
	 */
	UPROPERTY()
	TArray<UCharacterSkillBase*> ActiveSkills;
	
	/**
	 * @brief 被动技能列表
	 */
	UPROPERTY()
	TArray<UCharacterSkillBase*> PassiveSkills;

	/**
	 * @brief 当前释放的技能
	 */
	UPROPERTY()
	UCharacterSkillBase* CurrentSkill = nullptr;
};
