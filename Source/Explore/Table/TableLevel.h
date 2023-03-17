// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableLevel.generated.h"

USTRUCT(BlueprintType)
struct FTableLevelRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableLevel")
	int32 ID;

	/**
	 * @brief 当前等级升级需要的经验值
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableLevel")
	int32 Experience;

	/**
	 * @brief 当前等级升级需要的总经验值
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableLevel")
	int32 TotalExperience;
};

using FTableLevel = FTableBase<FTableLevelRowData>;