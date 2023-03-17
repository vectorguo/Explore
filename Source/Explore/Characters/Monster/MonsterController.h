// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "MonsterController.generated.h"

/**
 * 怪物控制器
 */
UCLASS()
class EXPLORE_API AMonsterController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief 获取随机巡逻点
	 * @return 随机巡逻点
	 */
	UFUNCTION(BlueprintCallable, Category="AI | Monster")
	FVector GetPatrolRandomPosition();

	/**
	 * @brief 获取目标
	 * @return 目标
	 */
	class AExploreCharacter* GetTarget() const;

	/**
	 * @brief 释放技能
	 * @return 技能是否释放成功
	 */
	EBTNodeResult::Type ReleaseSkill();

	/**
	 * @brief 死亡
	 */
	UFUNCTION(BlueprintCallable, Category="AI | Monster")
	void Die();

	/**
	 * @brief 复活
	 */
	UFUNCTION(BlueprintCallable, Category="AI | Monster")
	void Revive();

private:
	/**
	 * @brief 所属英雄
	 */
	UPROPERTY()
	class AMonsterBase* OwnerMonster = nullptr;
	
	/**
	 * @brief 出生位置
	 */
	FVector BirthPosition;
};
