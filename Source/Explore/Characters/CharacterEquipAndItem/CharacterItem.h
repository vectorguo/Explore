// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Explore/Characters/Hero/MainHeroStateStruct.h"
#include "UObject/Object.h"
#include "CharacterItem.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UCharacterItem : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief 添加道具效果
	 */
	void AddItemEffect();

	/**
	 * @brief 移除道具效果
	 */
	void RemoveItemEffect();

	/**
	 * @brief 获取持有该道具的角色
	 * @return 持有人
	 */
	FORCEINLINE class AExploreCharacter* GetHeroOwner() const
	{
		return HeroOwner;
	}

	/**
	 * @brief 设置武器持有人
	 * @param Char 武器持有人
	 */
	FORCEINLINE void SetHeroOwner(class AExploreCharacter* Char)
	{
		HeroOwner = Char;
	}

	/**
	 * @brief 获取道具数据
	 * @return 道具数据
	 */
	FORCEINLINE const FBackpackSlotData& GetItemData() const
	{
		return ItemData;
	}
	
	/**
	 * @brief 获取武器装备GUID
	 * @return 武器装备GUID
	 */
	FORCEINLINE int32 GetItemGuid() const
	{
		return ItemData.Guid;
	}
	
	/**
	 * @brief 获取武器装备ID
	 * @return 武器装备ID
	 */
	FORCEINLINE int32 GetItemTid() const
	{
		return ItemData.Tid;
	}

	/**
	 * @brief 设置道具数据
	 * @param InItemData 道具数据
	 */
	FORCEINLINE void SetItemData(const FBackpackSlotData* InItemData)
	{
		ItemData = *InItemData;
	}
protected:
	/**
	 * @brief 持有武器的角色
	 */
	UPROPERTY()
	class AExploreCharacter* HeroOwner = nullptr;
	
	/**
	 * @brief 装备数据
	 */
	FBackpackSlotData ItemData;

	/**
	 * @brief 装备附带的Buff的GUID列表
	 */
	UPROPERTY()
	TArray<int32> BuffGuids;
};
