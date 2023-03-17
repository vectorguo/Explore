#pragma once

#include "CharacterSkillBase.h"
#include "HeroSkillCommonAttack.generated.h"

UCLASS()
class EXPLORE_API UHeroSkillCommonAttack : public UCharacterSkillBase
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 技能更新
	 */
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * @brief 释放技能
	 */
	virtual void Release() override;

protected:
	/**
	 * @brief 获取技能主目标
	 * @return 技能目标
	 */
	virtual AExploreCharacter* GetMainTarget() const override;
	
private:
	/**
	 * @brief 是否需要向目标移动
	 */
	bool bMoveToTarget = false;

	/**
	 * @brief 是否需要向目标转向
	 */
	bool bRotateToTarget = false;
};
