// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowWidget.h"
#include "HeroInfoWindowWidget.generated.h"

/**
 * 游戏主界面
 */
UCLASS()
class EXPLORE_API UHeroInfoWindowWidget : public UWindowWidget
{
	GENERATED_BODY()

protected:
	UHeroInfoWindowWidget();
	virtual ~UHeroInfoWindowWidget() override;
	
public:
	/**
	 * @brief 初始化
	 * @return 初始化是否成功
	 */
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	/**
	 * @brief 刷新
	 */
	virtual void Refresh();

protected:
	/**
	 * @brief 点击装备切页
	 */
	UFUNCTION(BlueprintCallable)
	void OnClickEquipTab();

	/**
	 * @brief 点击道具切页
	 */
	UFUNCTION(BlueprintCallable)
	void OnClickItemTab();

private:
	/**
	 * @brief 初始化英雄数据
	 */
	void InitializeHero();
	
	/**
	 * @brief 初始化背包
	 */
	void InitializeBackpack();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<class UBackpackSlotWidget> BackpackSlotClass;

	/**
	 * @brief 玩家身上的装备(武器)
	 */
	UPROPERTY()
	TArray<UBackpackSlotWidget*> HeroEquipmentSlots;
	
	/**
	 * @brief 装备的Grid
	 */
	UPROPERTY()
	class UUniformGridPanel* BackpackEquipmentGrid;
	
	/**
	 * @brief 装备的ScrollBox
	 */
	UPROPERTY()
	class UScrollBox* BackpackEquipmentSb;
	
	/**
	 * @brief Item的Grid
	 */
	UPROPERTY()
	class UUniformGridPanel* BackpackItemGrid;

	/**
	 * @brief Item的ScrollBox
	 */
	UPROPERTY()
	class UScrollBox* BackpackItemSb;
};
