// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowWidget.h"
#include "ShopWindowWidget.generated.h"

struct FBackpackSlotData;

/**
 * 商店界面
 */
UCLASS()
class EXPLORE_API UShopWindowWidget : public UWindowWidget
{
	GENERATED_BODY()

protected:
	UShopWindowWidget();
	virtual ~UShopWindowWidget() override;
	
public:
	/**
	 * @brief 初始化
	 * @return 初始化是否成功
	 */
	virtual bool Initialize() override;

	/**
	 * @brief 初始化数据
	 * @param InShopTid 商店ID
	 */
	void InitializeData(int32 InShopTid);

private:
	/**
	 * @brief 金币变化回调
	 * @param Coin 当前金币数量
	 */
	UFUNCTION()
	void OnCoinChange(int32 Coin);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<class UShopCommodityWidget> ShopCommodityClass;

	/**
	 * @brief 玩家的金币数量
	 */
	UPROPERTY()
	class UTextBlock* CoinTxt;

	/**
	 * @brief 商品容器
	 */
	UPROPERTY()
	class UUniformGridPanel* ContainerGrid;
};
