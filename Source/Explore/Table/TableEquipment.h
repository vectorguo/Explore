#pragma once

#include "CoreMinimal.h"
#include "TableBase.h"
#include "Engine/DataTable.h"
#include "TableEquipment.generated.h"

USTRUCT(BlueprintType)
struct FTableEquipmentRowData : public FTableRowBase
{
	GENERATED_BODY();

public:
	/**
	 * @brief ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	int32 ID;

	/**
	 * @brief 装备名称
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	FString Name;

	/**
	 * @brief 装备描述
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	FString Description;

	/**
	 * @brief 装备Icon
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	FString Icon;

	/**
	 * @brief 装备品质
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	int32 Quality;
	
	/**
	 * @brief 装备部位
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	int32 Part;

	/**
	 * @brief 装备套装组ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	int32 Group;

	/**
	 * @brief 装备附带的属性
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	TArray<float> Attributes;
	
	/**
	 * @brief 装备附带的技能
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	TArray<int32> Skills;

	/**
	 * @brief 装备附带的Buff
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	TArray<int32> Buffs;

	/**
	 * @brief 出售价格
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	int32 SellPrice;
	
	/**
	 * @brief 装备是否拥有外观
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	int32 HasFacade;

	/**
	 * @brief 装备外观的蓝图路径
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	FString FacadePath;

	/**
	 * @brief 装备外观挂载的节点名称
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TableEquipment")
	FString SocketName;
};

using FTableEquipment = FTableBase<FTableEquipmentRowData>;