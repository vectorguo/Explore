// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ExploreTimeline.generated.h"

class AExploreCharacter;
class UExploreTimelineTemplate;
class UCharacterSkillBase;

/**
 * @brief Timeline状态
 */
UENUM(BlueprintType)
enum class ETimelineState : uint8
{
	ETS_None UMETA(DisplayName = "None"),
	ETS_Running UMETA(DisplayName = "Running"),
	ETS_Paused UMETA(DisplayName = "Paused"),
	ETS_Destroyed UMETA(DisplayName = "Destroyed"),
};

/**
 * Timeline
 */
UCLASS()
class EXPLORE_API UExploreTimeline : public UObject
{
	GENERATED_BODY()

	//友元
	friend class UExploreTimelineManager;

public:
	virtual ~UExploreTimeline() override
	{
	}
	
private:
	/**
	 * @brief 初始化
	 * @param InGuid Timeline的Guid
	 * @param InTid Timeline的Tid
	 * @param InTemplate Timeline模板
	 * @param InPlayRate Timeline播放速度
	 */
	void Initialize(int32 InGuid, int32 InTid, const UExploreTimelineTemplate* InTemplate, float InPlayRate);

	/**
	 * @brief 开始
	 */
	void Start();

	/**
	 * @brief Tick
	 * @param DeltaTime Tick时间
	 */
	void Tick(float DeltaTime);

	/**
	 * @brief 暂停
	 */
	void Pause();

	/**
	 * @brief 恢复
	 */
	void Resume();

	/**
	 * @brief 停止Timeline
	 * @param bNormal 是否是正常结束
	 */
	void Stop(bool bNormal = false);

public:
	/**
	 * @brief 获取Timeline的Guid
	 * @return Guid
	 */
	FORCEINLINE int32 GetGuid() const
	{
		return Guid;
	}

	/**
	 * @brief 获取Timeline的播放速度
	 * @return 播放速度
	 */
	FORCEINLINE float GetPlayRate() const
	{
		return PlayRate;
	}
	
	/**
	 * @brief 获取Timeline操作的角色
	 * @return Timeline操作的角色
	 */
	FORCEINLINE AExploreCharacter* GetCharacter() const
	{
		return Character;
	}

	/**
	 * @brief 设置Timeline操作的角色
	 * @param InCharacter Timeline操作的角色
	 */
	FORCEINLINE void SetCharacter(AExploreCharacter* InCharacter)
	{
		Character = InCharacter;
	}

	/**
	 * @brief 获取Timeline所属的Buff
	 * @return Timeline所属的Buff
	 */
	FORCEINLINE UCharacterBuffBase* GetBuff() const
	{
		return Buff;
	}

	/**
	 * @brief 设置Timeline所属的Buff
	 * @param InBuff Timeline所属的Buff
	 */
	FORCEINLINE void SetBuff(UCharacterBuffBase* InBuff)
	{
		Buff = InBuff;
	}
	
	/**
	 * @brief 获取Timeline所属的技能
	 * @return Timeline所属的技能
	 */
	FORCEINLINE UCharacterSkillBase* GetSkill() const
	{
		return Skill;
	}

	/**
	 * @brief 设置Timeline所属的技能
	 * @param InSkill Timeline所属的技能
	 */
	FORCEINLINE void SetSkill(UCharacterSkillBase* InSkill)
	{
		Skill = InSkill;
	}

	/**
	 * @brief 获取指定索引的特效
	 * @param Index 特效索引
	 * @return 特效
	 */
	AActor* GetEffect(int32 Index);
	
	/**
	 * @brief 获取状态
	 * @return 状态
	 */
	FORCEINLINE ETimelineState GetState() const
	{
		return State;
	}
	
private:
	
	/**
	 * @brief ID
	 */
	int32 Guid;

	/**
	 * @brief TID
	 */
	int32 Tid;

	/**
	 * @brief 模板
	 */
	UPROPERTY()
	const UExploreTimelineTemplate* Template;

	/**
	 * @brief 播放速度
	 */
	float PlayRate = 1.0f;

	/**
	 * @brief Timeline操作的角色
	 */
	UPROPERTY()
	AExploreCharacter* Character;

	/**
	 * @brief Timeline所属的Buff
	 */
	UPROPERTY()
	UCharacterBuffBase* Buff;
	
	/**
	 * @brief Timeline所属的技能
	 */
	UPROPERTY()
	UCharacterSkillBase* Skill;

	/**
	 * @brief 特效列表
	 */
	UPROPERTY()
	TMap<int32, AActor*> EffectsMap;
	
	/**
	 * @brief 状态
	 */
	ETimelineState State = ETimelineState::ETS_None;

	/**
	 * @brief 下一个要执行的Point索隐
	 */
	int32 NextPointIndex;

	/**
	 * @brief 运行时间
	 */
	float Duration;

	/**
	 * @brief Timeline结束时候的回调函数, 参数 0代表正常结束 1代表提前结束
	 */
	DECLARE_DELEGATE_OneParam(FSingleDelagateWithOneParam, int32);
	FSingleDelagateWithOneParam TimelineFinishDelegate;
};
