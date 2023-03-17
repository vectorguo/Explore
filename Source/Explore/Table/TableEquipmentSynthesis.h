// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableEquipmentSynthesis.generated.h"

USTRUCT(BlueprintType)
struct FTableEquipmentSynthesisRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipmentSynthesis")
	int32 ID;

	/**
	 * @brief Name
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipmentSynthesis")
	FString Name;

	/**
	 * @brief Description
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipmentSynthesis")
	FString Description;

	/**
	 * @brief 合成的装备TID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipmentSynthesis")
	int32 EquipmentTid;

	/**
	 * @brief 合成所需要的装备材料列表
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipmentSynthesis")
	TArray<int32> EquipMaterials;

	/**
	 * @brief 合成所需要的道具材料列表
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipmentSynthesis")
	TArray<int32> ItemMaterials;
};

using FTableEquipmentSynthesis = FTableBase<FTableEquipmentSynthesisRowData>;