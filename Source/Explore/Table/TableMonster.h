// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableMonster.generated.h"

USTRUCT(BlueprintType)
struct FTableMonsterRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	int32 ID;

	/**
	 * @brief 怪物名称
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	FString Name;
	
	/**
	 * @brief 怪物技能
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	TArray<int32> Skills;

	/**
	 * @brief 怪物高度
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	float Height;

	/**
	 * @brief 移动速度
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	float MoveSpeed;

	/**
	 * @brief 视野范围
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	float SightRadius;

	/**
	 * @brief 丢失视野范围
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	float LoseSightRadius;

	/**
	 * @brief 掉落道具
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	int32 DropItem;
	
	/**
	 * @brief 掉落金币
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	int32 DropCoin;

	/**
	 * @brief 死亡表现
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableMonster")
	int32 Death;
};

using FTableMonster = FTableBase<FTableMonsterRowData>;