#pragma once

#include "CharacterSkillBase.h"
#include "HeroSkillSprintAttack.generated.h"

UCLASS()
class EXPLORE_API UHeroSkillSprintAttack : public UCharacterSkillBase
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 初始化
	 * @param Character 技能拥有者
	 * @param SkillConfig 技能配置
	 */
	virtual void Initialize(AExploreCharacter* Character, const struct FTableSkillRowData* InSkillConfig) override;
	
	/**
	 * @brief 是否可用
	 * @return 是否可用
	 */
	virtual bool IsValid() override;

	/**
	 * @brief 技能更新
	 */
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * @brief 释放技能
	 */
	virtual void Release() override;

	/**
	 * @brief 停止释放技能
	 */
	virtual void Stop() override;

	/**
	 * @brief 设置冲刺速度
	 * @param Speed 冲刺速度
	 */
	FORCEINLINE void SetSprintSpeed(float Speed)
	{
		SprintSpeed = Speed;
	}
	
private:
	/**
	 * @brief 冲刺速度
	 */
	float SprintSpeed = 0.0f;

	/**
	 * @brief 冲刺方向
	 */
	FVector SprintDirection;

	/**
	 * @brief 冲刺时间
	 */
	float SprintTime = -1.0f;

	/**
	 * @brief 技能目标缓存
	 */
	UPROPERTY()
	class AMonsterBase* TargetCache = nullptr;
};
