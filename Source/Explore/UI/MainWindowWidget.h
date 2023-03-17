// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowWidget.h"
#include "MainWindowWidget.generated.h"

/**
 * 游戏主界面
 */
UCLASS()
class EXPLORE_API UMainWindowWidget : public UWindowWidget
{
	GENERATED_BODY()

protected:
	UMainWindowWidget();
	
public:
	/**
	 * @brief 初始化
	 * @return 初始化是否成功
	 */
	virtual bool Initialize() override;

private:
	/**
	 * @brief 血量变化回调
	 * @param Attribute 英雄属性
	 * @param Health 英雄当前血量
	 * @param HealthDelta 英雄血量变化值
	 */
	UFUNCTION()
	void OnHealthChange(class UCharacterAttribute* Attribute, float Health, float HealthDelta);

	/**
	 * @brief 最大血量变化回调
	 * @param Attribute 英雄属性
	 * @param Health 英雄最大血量
	 * @param HealthDelta 英雄最大血量变化值
	 */
	UFUNCTION()
	void OnMaxHealthChange(class UCharacterAttribute* Attribute, float Health, float HealthDelta);

	/**
	 * @brief 经验值变化回调
	 * @param Attribute 英雄属性
	 * @param Experience 英雄经验值
	 */
	UFUNCTION()
	void OnExperienceChange(class UCharacterAttribute* Attribute, float Experience);

	/**
	 * @brief 等级变化回调
	 * @param Attribute 英雄属性
	 * @param Level 英雄等级
	 */
	UFUNCTION()
	void OnLevelChange(class UCharacterAttribute* Attribute, int32 Level);

	/**
	 * @brief 金币变化回调
	 * @param Coin 当前金币数量
	 */
	UFUNCTION()
	void OnCoinChange(int32 Coin);

protected:
	/**
	 * @brief 等级文本框
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LevelTxt;
	
	/**
	 * @brief 经验条
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* ExperienceBar;

	/**
	 * @brief 经验值文本框
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ExperienceTxt;

	/**
	 * @brief 血量条
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;

	/**
	 * @brief 血量文本框
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HealthTxt;
	/**
	 * @brief 魔法条
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* MagicBar;

	/**
	 * @brief 魔法文本框
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* MagicTxt;

	/**
	 * @brief 金币框
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinValueTxt;
};
