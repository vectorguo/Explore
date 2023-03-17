// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Explore/Table/TableBuff.h"
#include "UObject/Object.h"
#include "CharacterBuffBase.generated.h"

class AExploreCharacter;

/**
 * @brief Buff类型
 */
UENUM(BlueprintType)
enum class EBuffType : uint8
{
	EBT_Attribute			UMETA(DisplayName = "Property"),			//属性类Buff
	EBT_ChangingAttribute	UMETA(DisplayName = "ChangingAttribute"),	//变化属性类Buff
	EBT_BeforeAttack		UMETA(DisplayName = "BeforeAttack"),		//攻击前触发类
	EBT_AfterAttack			UMETA(DisplayName = "AfterAttack"),			//攻击后触发类
	EBT_BeHit				UMETA(DisplayName = "BeHit"),				//被击触发类
	EBT_Status				UMETA(DisplayName = "Status"),				//状态类Buff
};

/**
 * @brief Buff效果类型
 */
UENUM(BlueprintType)
enum class EBuffEffectType : uint8
{
	EBET_Common		UMETA(DisplayName = "Common"),		//普通类型
	EBET_Gain		UMETA(DisplayName = "Gain"),		//增益Buff
	EBET_DeBuff		UMETA(DisplayName = "DeBuff"),		//减益Buff
};

/**
 * @brief Buff状态
 */
UENUM(BlueprintType)
enum class EBuffState : uint8
{
	EBS_None		UMETA(DisplayName = "None"),
	EBS_Running		UMETA(DisplayName = "Running"),
	EBS_Finished	UMETA(DisplayName = "Finished"),
};

/**
 * 
 */
UCLASS()
class EXPLORE_API UCharacterBuffBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(int32 ID, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser)
	{
		Guid = ID;
		Owner = BuffOwner;
		Causer = BuffCauser;
	}
	
	/**
	 * @brief 初始化
	 * @param InGuid Buff的唯一ID
	 * @param BuffOwner
	 * @param BuffCauser
	 * @param BuffConfig 技能配置
	 */
	virtual void Initialize(int32 InGuid, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser, const struct FTableBuffRowData* BuffConfig)
	{
		Guid = InGuid;
		Owner = BuffOwner;
		Causer = BuffCauser;

		BuffType = static_cast<EBuffType>(BuffConfig->Type);
		BuffGroup = BuffConfig->Group;
		BuffEffectType = static_cast<EBuffEffectType>(BuffConfig->EffectType);
		BuffState = EBuffState::EBS_Running;
		Duration = BuffConfig->Duration;
	}

	/**
	 * @brief Buff生效
	 */
	virtual void TakeEffect()
	{
		
	}

	/**
	 * @brief 攻击前生效
	 * @param Target 目标
	 */
	virtual void TakeEffectBeforeAtk(AExploreCharacter* Target)
	{
		
	}

	/**
	 * @brief 攻击后生效
	 * @param Target 目标
	 */
	virtual void TakeEffectAfterAtk(AExploreCharacter* Target)
	{
		
	}

	/**
	 * @brief 更新
	 * @param DeltaTime 更新时间
	 */
	virtual void Tick(float DeltaTime)
	{
		if (Duration >= 0)
		{
			CurrentDuration += DeltaTime;
			if (CurrentDuration >= Duration)
			{
				Destroy(true);
				BuffState = EBuffState::EBS_Finished;
			}
		}
	}

	/**
	 * @brief 销毁
	 * @param bNormal 是否正常结束
	 */
	virtual void Destroy(bool bNormal)
	{
		
	}

	/**
	 * @brief 造成伤害
	 */
	virtual void ApplyDamage()
	{
		
	}
	
	/**
	 * @brief 获取Buff唯一ID
	 * @return 唯一ID
	 */
	FORCEINLINE int32 GetGUID() const
	{
		return Guid;
	}
	
	/**
	 * @brief 获取Buff拥有者
	 * @return Buff拥有者
	 */
	FORCEINLINE AExploreCharacter* GetOwner() const
	{
		return Owner;
	}

	/**
	 * @brief 获取Buff施加者
	 * @return Buff施加者
	 */
	FORCEINLINE AExploreCharacter* GetCauser() const
	{
		return Causer;
	}

	/**
	 * @brief 获取Buff类型
	 * @return Buff类型
	 */
	FORCEINLINE EBuffType GetBuffType() const
	{
		return BuffType;
	}

	/**
	 * @brief 获取Buff组
	 * @return Buff组
	 */
	FORCEINLINE int32 GetBuffGroup() const
	{
		return BuffGroup;
	}

	/**
	 * @brief 获取Buff效果类型
	 * @return Buff效果类型
	 */
	FORCEINLINE EBuffEffectType GetBuffEffectType() const
	{
		return BuffEffectType;
	}

	/**
	 * @brief 获取Buff状态
	 * @return Buff状态
	 */
	FORCEINLINE EBuffState GetBuffState() const
	{
		return BuffState;
	}

protected:
	/**
	 * @brief GUID
	 */
	int32 Guid;
	
	/**
	 * @brief Buff拥有者
	 */
	UPROPERTY()
	AExploreCharacter* Owner = nullptr;

	/**
	 * @brief Buff施加者
	 */
	UPROPERTY()
	AExploreCharacter* Causer = nullptr;

	/**
	 * @brief Buff类型
	 */
	EBuffType BuffType;

	/**
	 * @brief Buff组
	 */
	int32 BuffGroup = -1;

	/**
	 * @brief Buff效果类型
	 */
	EBuffEffectType BuffEffectType;

	/**
	 * @brief Buff持续时间
	 */
	float Duration = 0;

	/**
	 * @brief Buff状态
	 */
	EBuffState BuffState = EBuffState::EBS_None;
	
	/**
	 * @brief 当前持续时间
	 */
	float CurrentDuration = 0;
};
