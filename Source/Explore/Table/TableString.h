// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableString.generated.h"

USTRUCT(BlueprintType)
struct FTableStringRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	int32 ID;

	/**
	 * @brief 字符串
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableShop")
	FString Content;
};

using FTableString = FTableBase<FTableStringRowData>;