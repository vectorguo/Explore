// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableDropItem.generated.h"

USTRUCT(BlueprintType)
struct FTableDropItemRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableDropItem")
	int32 ID;

	/**
	 * @brief 掉落包名称
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableDropItem")
	FString Name;

	/**
	 * @brief 掉落的装备
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableDropItem")
	TArray<int32> DropEquipments;

	/**
	 * @brief 掉落的道具
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableDropItem")
	TArray<int32> DropItems;
};

using FTableDropItem = FTableBase<FTableDropItemRowData>;