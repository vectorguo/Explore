// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableShop.generated.h"

USTRUCT(BlueprintType)
struct FTableShopRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	int32 ID;

	/**
	 * @brief 商店名称
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	FString Name;

	/**
	 * @brief 商店里卖的装备
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	TArray<int32> Equipments;
	
	/**
	 * @brief 商店里卖的道具
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	TArray<int32> Items;
};

using FTableShop = FTableBase<FTableShopRowData>;