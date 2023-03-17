// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Hero/MainHero.h"
#include "UObject/Object.h"
#include "ExploreGameManager.generated.h"

/**
 * 单例类
 */
UCLASS()
class EXPLORE_API UExploreGameManager : public UObject
{
	GENERATED_BODY()

public:
	UExploreGameManager(){}
	virtual ~UExploreGameManager() override;

	/**
	 * @brief 获取单例
	 * @return 单例
	 */
	UFUNCTION(BlueprintCallable, Category= "GameManager")
	static UExploreGameManager* GetInstance();
	
	/**
	 * @brief 初始化
	 */
	void Initialize();

	/**
	 * @brief 初始化配置表
	 */
	void InitializeTables() const;

	/**
	 * @brief 获取主英雄
	 * @return 主英雄
	 */
	FORCEINLINE class AMainHero* GetMainHero() const
	{
		return MainHero;
	}

	/**
	 * @brief 获取英雄的背包
	 * @return 背包
	 */
	class AMainHeroState* GetMainHeroBackpack() const
	{
		return MainHero ? MainHero->GetBackpack() : nullptr;
	}

	/**
	 * @brief 设置主英雄
	 * @param Hero 主英雄
	 */
	void SetMainHero(class AMainHero* Hero);

	/**
	 * @brief 获取Timeline Manager
	 * @return Timeline Manager
	 */
	FORCEINLINE class UExploreTimelineManager* GetTimelineManager() const
	{
		return TimelineManager;
	}

private:

	/**
	 * @brief 卸载配置表
	 */
	void DestroyTables() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category= "GameManager")
	class AMainHero* MainHero = nullptr;

	UPROPERTY()
	class UExploreTimelineManager* TimelineManager;
};
