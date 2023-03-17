// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableSkill.generated.h"

USTRUCT(BlueprintType)
struct FTableSkillRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 ID;

	/**
	 * @brief 技能描述
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	FString Description;

	/**
	 * @brief 技能种类
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 Kind;
	
	/**
	 * @brief 技能释放优先级
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 Priority;

	/**
	 * @brief 技能释放概率
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 Probability;

	/**
	 * @brief 技能释放模式
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 Mode;

	/**
	 * @brief 技能类型
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 Type;

	/**
	 * @brief 技能元素类型
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 Element;

	/**
	 * @brief 技能Timeline
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 Timeline;

	/**
	 * @brief 技能CD
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	float CD;

	/**
	 * @brief 伤害类型
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 DamageType;

	/**
	 * @brief 伤害参数
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	TArray<float> DamageParams;

	/**
	 * @brief 技能施法范围
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	float ReleasingRange;

	/**
	 * @brief 技能索敌范围
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	float SearchingRange;

	/**
	 * @brief 技能释放时是否需要转向目标
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 NeedRotateToTarget;

	/**
	 * @brief 动态技能速度
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableSkill")
	int32 DynamicSkillSpeed;
};

using FTableSkill = FTableBase<FTableSkillRowData>;