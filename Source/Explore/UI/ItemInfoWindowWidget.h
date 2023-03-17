// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowWidget.h"
#include "Explore/ExploreEnum.h"
#include "ItemInfoWindowWidget.generated.h"

struct FBackpackSlotData;

/**
 * 装备信息界面
 */
UCLASS()
class EXPLORE_API UItemInfoWindowWidget : public UWindowWidget
{
	GENERATED_BODY()

protected:
	UItemInfoWindowWidget();
	virtual ~UItemInfoWindowWidget() override;
	
public:
	/**
	 * @brief 初始化
	 * @return 初始化是否成功
	 */
	virtual bool Initialize() override;

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

protected:
	/**
	 * @brief Slot数据
	 */
	const FBackpackSlotData* ItemData = nullptr;

	/**
	 * @brief 上下文
	 */
	EBackpackSlotContext Context;
	
	/**
	 * @brief 装备Slot
	 */
	UPROPERTY()
	class UBackpackSlotWidget* ItemSlot;

	/**
	 * @brief 装备名称
	 */
	UPROPERTY()
	class UTextBlock* ItemNameTxt;

	/**
	 * @brief 装备等级
	 */
	UPROPERTY()
	class UTextBlock* ItemLevelTxt;

	/**
	 * @brief 装备描述
	 */
	UPROPERTY()
	class UTextBlock* ItemDescriptionTxt;
	
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
