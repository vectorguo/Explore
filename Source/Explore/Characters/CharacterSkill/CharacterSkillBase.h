#pragma once

#include "CoreMinimal.h"
#include "Explore/Table/TableSkill.h"
#include "Explore/ExploreEnum.h"
#include "UObject/Object.h"
#include "CharacterSkillBase.generated.h"

class AExploreCharacter;

/**
 * @brief 技能模式
 */
UENUM(BlueprintType)
enum class ECharacterSkillMode : uint8
{
	ECSM_InHand		UMETA(DisplayName = "InHand"),		//在手技能
	ECSM_OutOfHand	UMETA(DisplayName = "OutOfHand"),	//脱手技能
};

/**
 * @brief 技能类型
 */
UENUM(BlueprintType)
enum class ECharacterSkillType : uint8
{
	ECST_Passive	UMETA(DisplayName = "Passive"),		//被动技能
	ECST_Active		UMETA(DisplayName = "Active"),		//主动技能
};

/**
 * @brief 技能状态
 */
UENUM(BlueprintType)
enum class ECharacterSkillState : uint8
{
	ECSS_None		UMETA(DisplayName = "None"),
	ECSS_Ready		UMETA(DisplayName = "Ready"),
	ECSS_Releasing	UMETA(DisplayName = "Releasing"),
	ECSS_Finished	UMETA(DisplayName = "Finished"),
};

UCLASS()
class UCharacterSkillBase : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief 初始化
	 * @param Character 技能拥有者
	 * @param InSkillConfig 技能配置
	 */
	virtual void Initialize(AExploreCharacter* Character, const struct FTableSkillRowData* InSkillConfig);
	
	/**
	 * @brief 技能更新
	 */
	virtual void Tick(float DeltaTime)
	{
		
	}
	
	/**
	 * @brief 释放技能
	 */
	virtual void Release();

	/**
	 * @brief 停止释放技能
	 */
	virtual void Stop();

	/**
	 * @brief 是否可用
	 * @return 是否可用
	 */
	virtual bool IsValid()
	{
		return true;
	}

	/**
	 * @brief 造成伤害
	 */
	void ApplyDamage();

	/**
	 * @brief 获取技能ID
	 * @return ID
	 */
	FORCEINLINE uint32 GetSkillID() const
	{
		return SkillID;
	}
	
	/**
	 * @brief 获取技能优先级
	 * @return 优先级
	 */
	FORCEINLINE uint32 GetSkillPriority() const
	{
		return SkillConfig->Priority;
	}

	/**
	 * @brief 获取技能释放概率(0 ~ 100)
	 * @return 概率
	 */
	FORCEINLINE uint32 GetSkillProbability() const
	{
		return SkillProbability;
	}

	/**
	 * @brief 获取技能模式
	 * @return 技能模式
	 */
	FORCEINLINE ECharacterSkillMode GetSkillMode() const
	{
		return static_cast<ECharacterSkillMode>(SkillConfig->Mode);
	}

	/**
	 * @brief 获取技能类型
	 * @return 技能类型
	 */
	FORCEINLINE ECharacterSkillType GetSkillType() const
	{
		return static_cast<ECharacterSkillType>(SkillConfig->Type);
	}

	/**
	 * @brief 获取技能元素类型
	 * @return 技能元素类型
	 */
	FORCEINLINE ECharacterElement GetSkillElement() const
	{
		return SkillElement;
	}

	/**
	 * @brief 设置技能元素类型
	 * @param Element 技能元素类型
	 */
	FORCEINLINE void SetSkillElement(ECharacterElement Element)
	{
		SkillElement = Element;
	}
	
	/**
	 * @brief 获取施法距离
	 * @return 施法距离
	 */
	FORCEINLINE float GetReleasingRange() const
	{
		return SkillConfig->ReleasingRange;
	}

	/**
	 * @brief 获取施法距离的平方
	 * @return 施法距离的平方
	 */
	FORCEINLINE float GetReleasingRangeSquared() const
	{
		return SkillConfig->ReleasingRange * SkillConfig->ReleasingRange;
	}

	/**
	 * @brief 获取索敌范围
	 * @return 索敌范围
	 */
	FORCEINLINE float GetSearchingRange() const
	{
		return SkillConfig->SearchingRange;
	}

	/**
	 * @brief 获取索敌范围的平方
	 * @return 索敌范围的平方
	 */
	FORCEINLINE float GetSearchingRangeSquared() const
	{
		return SkillConfig->SearchingRange * SkillConfig->SearchingRange;
	}
	
	/**
	 * @brief 获取技能播放速度
	 */
	float GetSkillSpeed() const;

	/**
	 * @brief 释放技能的时候是否需要转向技能目标
	 * @return 是否需要转向
	 */
	FORCEINLINE bool NeedRotateToTarget() const
	{
		return SkillConfig->NeedRotateToTarget == 1;
	}

	/**
	 * @brief 获取技能状态
	 * @return 技能状态
	 */
	FORCEINLINE ECharacterSkillState GetSkillState() const
	{
		return SkillState;
	}

	/**
	 * @brief 设置技能状态
	 * @param State 技能状态
	 */
	FORCEINLINE void SetSkillState(ECharacterSkillState State)
	{
		SkillState = State;
	}
	
	/**
	 * @brief 技能是否没有被锁定，即可以被移动操作打断
	 * @return 技能是否没有被锁定，即可以被移动操作打断
	 */
	FORCEINLINE bool IsUnlock() const
	{
		return bUnlock;
	}

	FORCEINLINE void SetUnlock(bool bIsUnlock)
	{
		bUnlock = bIsUnlock;
	}

protected:
	/**
	 * @brief 播放Timeline
	 */
	void PlayTimeline();

	/**
	 * @brief Timeline结束的回调函数
	 * @param EndContext Timeline结束时候的上下文 0代表正常结束 1代表提前终止
	 */
	virtual void OnTimelineEnd(int32 EndContext);

	/**
	 * @brief 获取技能主目标
	 * @return 技能目标
	 */
	virtual AExploreCharacter* GetMainTarget() const
	{
		return nullptr;
	}

	/**
	 * @brief 单体伤害
	 */
	virtual void ApplyDamage_SingleTarget();

protected:
	/**
	 * @brief 获取技能伤害系数
	 * @return 技能伤害系数
	 */
	FORCEINLINE float GetDamageRatio() const
	{
		return SkillConfig->DamageParams[0];
	}

protected:
	/**
	 * @brief 技能拥有者
	 */
	UPROPERTY()
	AExploreCharacter* Owner;

	/**
	 * @brief 技能配置
	 */
	const struct FTableSkillRowData* SkillConfig;
	
	/**
	 * @brief 技能ID
	 */
	uint32 SkillID;

	/**
	 * @brief 释放概率(0 ~ 100)
	 */
	uint32 SkillProbability;

	/**
	 * @brief 技能状态
	 */
	ECharacterSkillState SkillState = ECharacterSkillState::ECSS_None;

	/**
	 * @brief 技能元素类型
	 */
	ECharacterElement SkillElement = ECharacterElement::ECE_None;

	/**
	 * @brief 冷却时间
	 */
	float CD;

	/**
	 * @brief 技能是否没有被算定，即可以被移动操作打断
	 */
	bool bUnlock = true;

	/**
	 * @brief 上一次释放技能的时间
	 */
	float LastSkillReleaseTime = 0;

	/**
	 * @brief Timeline唯一ID
	 */
	int32 TimelineGuid = -1;
};
