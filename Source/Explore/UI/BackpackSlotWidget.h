// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Explore/ExploreEnum.h"
#include "BackpackSlotWidget.generated.h"

struct FBackpackSlotData;

/**
 * 游戏主界面
 */
UCLASS()
class EXPLORE_API UBackpackSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 析构
	 */
	virtual ~UBackpackSlotWidget() override;

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
	void InitializeData(const FBackpackSlotData& Data, EBackpackSlotContext InContext);

	/**
	 * @brief 清理数据
	 */
	void ClearData();

protected:
	/**
	 * @brief 点击回调
	 */
	UFUNCTION(BlueprintCallable)
	void OnClick();

protected:
	/**
	 * @brief Slot数据
	 */
	FBackpackSlotData* SlotData = nullptr;

	/**
	 * @brief 上下文类型
	 */
	EBackpackSlotContext Context;

	/**
	 * @brief 品质框
	 */
	UPROPERTY()
	class UImage* QualityImg;
	
	/**
	 * @brief Icon
	 */
	UPROPERTY()
	class UImage* IconImg;

	/**
	 * @brief 数量
	 */
	UPROPERTY()
	class UTextBlock* CountTxt;
};
