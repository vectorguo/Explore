// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopCommodityWidget.generated.h"

/**
 * 游戏主界面
 */
UCLASS()
class EXPLORE_API UShopCommodityWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief 析构
	 */
	virtual ~UShopCommodityWidget() override;

	/**
	 * @brief 初始化数据
	 * @param InTid Tid
	 * @param InPrice 价格
	 * @param Coin 英雄拥有的金币数量
	 * @param bIsEquip 是否时装备
	 */
	void InitializeData(int32 InTid, int32 InPrice, int32 Coin, bool bIsEquip);

	/**
	 * @brief 刷新
	 * @param Coin 英雄拥有的金币数量
	 */
	void Refresh(int32 Coin);

	/**
	 * @brief 获取商品品质
	 * @return 商品品质
	 */
	int32 GetCommodityQuality() const;
	
protected:
	/**
	 * @brief 商品点击事件
	 */
	UFUNCTION(BlueprintCallable)
	void OnClick();
	
	/**
	 * @brief 购买按钮点击事件
	 */
	UFUNCTION(BlueprintCallable)
	void OnClickBuy();

protected:
	/**
	 * @brief 商品Tid
	 */
	int32 Tid;

	/**
	 * @brief 商品价格
	 */
	int32 Price;

	/**
	 * @brief 是否时装备
	 */
	int32 bIsEquipment;
};
