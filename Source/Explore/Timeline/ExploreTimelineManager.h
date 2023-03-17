// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExploreTimeline.h"
#include "UObject/Object.h"
#include "ExploreTimelineManager.generated.h"

class AExploreCharacter;
class UCharacterBuffBase;
class UCharacterSkillBase;
class UExploreTimelinePoint;
class UExploreTimelineTemplate;

/**
 * 
 */
UCLASS()
class EXPLORE_API UExploreTimelineManager : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief 更新
	 * @param DeltaTime 更新时间
	 */
	void Tick(float DeltaTime);

	/**
	 * @brief 播放Timeline
	 * @param InTid Timeline的配置ID
	 * @param InPlayRate Timeline播放速度
	 * @param InCharacter Timeline操作的角色
	 * @return Timeline的GUID
	 */
	int32 PlayTimeline(int32 InTid, float InPlayRate, class AExploreCharacter* InCharacter);

	template <typename T>
	int32 PlayTimeline(int32 InTid, float InPlayRate, AExploreCharacter* InCharacter, T* Obj, void (T::*Func)(int32))
	{
		auto* Timeline = CreateTimeline(InTid, InPlayRate, InCharacter);
		Timeline->TimelineFinishDelegate.BindUObject(Obj, Func);
		Timeline->Start();
		return Timeline->GetGuid();
	}
	
	/**
	 * @brief 播放Timeline
	 * @param InTid Timeline的配置ID
	 * @param InPlayRate Timeline播放速度
	 * @param InCharacter Timeline操作的角色
	 * @param Skill Timeline所属的技能
	 * @return Timeline的GUID
	 */
	int32 PlayTimeline(int32 InTid, float InPlayRate, AExploreCharacter* InCharacter, UCharacterSkillBase* Skill);

	template <typename T>
	int32 PlayTimeline(int32 InTid, float InPlayRate, AExploreCharacter* InCharacter, UCharacterSkillBase* Skill, T* Obj, void (T::*Func)(int32))
	{
		auto* Timeline = CreateTimeline(InTid, InPlayRate, InCharacter);
		Timeline->TimelineFinishDelegate.BindUObject(Obj, Func);
		Timeline->SetSkill(Skill);
		Timeline->Start();
		return Timeline->GetGuid();
	}
	
	/**
	 * @brief 播放Timeline
	 * @param InTid Timeline的配置ID
	 * @param InPlayRate Timeline播放速度
	 * @param InCharacter Timeline操作的角色
	 * @param Buff Timeline所属的Buff
	 * @return Timeline的GUID
	 */
	int32 PlayTimeline(int32 InTid, float InPlayRate, AExploreCharacter* InCharacter, UCharacterBuffBase* Buff);
	
	template <typename T>
	int32 PlayTimeline(int32 InTid, float InPlayRate, AExploreCharacter* InCharacter, UCharacterBuffBase* Buff, T* Obj, void (T::*Func)(int32))
	{
		auto* Timeline = CreateTimeline(InTid, InPlayRate, InCharacter);
		Timeline->TimelineFinishDelegate.BindUObject(Obj, Func);
		Timeline->SetBuff(Buff);
		Timeline->Start();
		return Timeline->GetGuid();
	}

	/**
	 * @brief 暂停Timeline
	 * @param InGuid Timeline的GUID
	 */
	void PauseTimeline(int32 InGuid);

	/**
	 * @brief 恢复暂停的Timeline
	 * @param InGuid Timeline的GUID
	 */
	void ResumeTimeline(int32 InGuid);

	/**
	 * @brief 停止Timeline
	 * @param InGuid Timeline的GUID
	 */
	void StopTimeline(int32 InGuid);

private:
	/**
	 * @brief 创建Timeline
	 * @param InTid Timeline的配置ID
	 * @param PlayRate Timeline播放速度
	 * @param InCharacter Timeline操作的角色
	 * @return Timeline
	 */
	UExploreTimeline* CreateTimeline(int32 InTid, float PlayRate, class AExploreCharacter* InCharacter);

	/**
	 * @brief 获取指定Guid的Timeline
	 * @param InGuid Timeline的Guid
	 * @return Timeline
	 */
	UExploreTimeline* GetTimeline(int32 InGuid);

private:
	/**
	 * @brief Timeline模板
	 */
	UPROPERTY()
	TMap<int32, const UExploreTimelineTemplate*> Templates;

	/**
	 * @brief 正在播放的所有Timeline
	 */
	UPROPERTY()
	TMap<int32, UExploreTimeline*> Timelines;

	/**
	 * @brief 新创建的Timeline
	 */
	UPROPERTY()
	TArray<UExploreTimeline*> NewTimelines;
};
