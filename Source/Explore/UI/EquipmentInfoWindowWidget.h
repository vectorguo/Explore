// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowWidget.h"
#include "Explore/ExploreEnum.h"
#include "EquipmentInfoWindowWidget.generated.h"

struct FBackpackSlotData;

/**
 * 装备信息界面
 */
UCLASS()
class EXPLORE_API UEquipmentInfoWindowWidget : public UWindowWidget
{
	GENERATED_BODY()

protected:
	UEquipmentInfoWindowWidget();
	virtual ~UEquipmentInfoWindowWidget() override;
	
public:
	/**
	 * @brief 初始化
	 * @return 初始化是否成功
	 */
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	/**
	 * @brief 初始化数据
	 * @param Data 数据
	 * @param InContext 上下文类型
	 */
	void InitializeData(const FBackpackSlotData* Data, EBackpackSlotContext InContext);

protected:
	/**
	 * @brief 按钮点击回调
	 */
	UFUNCTION(BlueprintCallable)
	void OnClickOperation();

	/**
	 * @brief 出售按钮点击回调
	 */
	UFUNCTION(BlueprintCallable)
	void OnClickSell();

private:
	/**
	 * @brief 穿戴装备
	 */
	void PutOnEquipment();

	/**
	 * @brief 脱下装备
	 */
	void TakeOffEquipment();

protected:
	/**
	 * @brief Slot数据
	 */
	const FBackpackSlotData* EquipmentData = nullptr;

	/**
	 * @brief 上下文
	 */
	EBackpackSlotContext Context;
	
	/**
	 * @brief 装备Slot
	 */
	UPROPERTY()
	class UBackpackSlotWidget* EquipmentSlot;

	/**
	 * @brief 装备名称
	 */
	UPROPERTY()
	class UTextBlock* EquipmentName;

	/**
	 * @brief 装备等级
	 */
	UPROPERTY()
	class UTextBlock* EquipmentLevel;

	/**
	 * @brief 装备描述
	 */
	UPROPERTY()
	class UTextBlock* EquipmentDescription;

	/**
	 * @brief 装备效果Grid
	 */
	UPROPERTY()
	class UVerticalBox* EquipmentEffects;

	/**
	 * @brief 操作按钮
	 */
	UPROPERTY()
	class USizeBox* OperationBtnParent;

	/**
	 * @brief 操作按钮名称
	 */
	UPROPERTY()
	class UTextBlock* OperationNameTxt;

	/**
	 * @brief 出售按钮
	 */
	UPROPERTY()
	class USizeBox* SellBtnParent;
};
