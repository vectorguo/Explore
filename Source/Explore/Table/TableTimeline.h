// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableTimeline.generated.h"

USTRUCT(BlueprintType)
struct FTableTimelineRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	int32 ID;

	/**
	 * @brief Timeline名称
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	FString Name;

	/**
	 * @brief Timeline参数
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	TArray<float> Params;

	/**
	 * @brief Timeline参数
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	TArray<int32> Effects;
};

using FTableTimeline = FTableBase<FTableTimelineRowData>;