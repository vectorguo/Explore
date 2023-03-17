// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableBuff.generated.h"

USTRUCT(BlueprintType)
struct FTableBuffRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	int32 ID;

	/**
	 * @brief Buff描述
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	FString Description;

	/**
	 * @brief Buff种类
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	int32 Kind;
	
	/**
	 * @brief Buff类型
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	int32 Type;

	/**
	 * @brief Buff替换规则
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	int32 ReplacementRule;

	/**
	 * @brief Buff组
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	int32 Group;
	
	/**
	 * @brief Buff参数
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	TArray<float> Params;

	/**
	 * @brief 效果类型
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	int32 EffectType;

	/**
	 * @brief Buff持续时间
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableBuff")
	float Duration;
};

using FTableBuff = FTableBase<FTableBuffRowData>;