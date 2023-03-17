#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableItem.generated.h"

USTRUCT(BlueprintType)
struct FTableItemRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	int32 ID;

	/**
	 * @brief 道具名称
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	FString Name;

	/**
	 * @brief 道具描述
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	FString Description;

	/**
	 * @brief 道具Icon
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	FString Icon;

	/**
	 * @brief 道具品质
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	int32 Quality;
	
	/**
	 * @brief 道具是否可以堆叠
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	int32 Stacked;

	/**
	 * @brief 道具是否可以使用
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	int32 Use;

	/**
	 * @brief 道具使用条件
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	int32 UseCondition;

	/**
	 * @brief 道具使用后是否销毁
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	int32 DestroyAfterUse;

	/**
	 * @brief 装备附带的属性
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	TArray<float> Attributes;
	
	/**
	 * @brief 装备附带的技能
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	TArray<int32> Skills;

	/**
	 * @brief 装备附带的Buff
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableItem")
	TArray<int32> Buffs;

	/**
	 * @brief 出售价格
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	int32 SellPrice;
};

using FTableItem = FTableBase<FTableItemRowData>;