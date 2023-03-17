// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainHeroStateStruct.h"
#include "MainHeroState.generated.h"

//声明一个动态广播委托
//第一个参数事件的名称（自己定义）
//后面的参数是事件所需要的参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHeroStateChangeSignatureI, int32, Value);

/**
 * 
 */
UCLASS()
class EXPLORE_API AMainHeroState : public APlayerState
{
	GENERATED_BODY()

public:
	/**
	 * @brief 获取金币数量
	 * @return 金币数量
	 */
	FORCEINLINE int32 GetCoin() const
	{
		return Coin;
	}

	/**
	 * @brief 增加金币
	 * @param Value 增加的金币数量
	 */
	FORCEINLINE void AddCoin(int32 Value)
	{
		Coin += Value;
		OnCoinChange.Broadcast(Coin);
	}

	/**
	 * @brief 生成Guid
	 * @return Guid
	 */
	static int32 GenerateGuid();
	
	/**
	 * @brief 获取玩家身上的装备数据
	 * @return 玩家身上的装备数据
	 */
	FORCEINLINE const TArray<FBackpackSlotData>& GetEquipmentDatas() const
	{
		return EquipmentDatas;
	}

	/**
	 * @brief 添加装备到背包
	 * @param EquipmentTid 装备Tid
	 */
	void AddEquipmentToBackpack(int32 EquipmentTid);

	/**
	 * @brief 添加装备到背包
	 * @param EquipmentData 装备数据
	 */
	void AddEquipmentToBackpack(const FBackpackSlotData& EquipmentData);

	/**
	 * @brief 将装备从背包中移除
	 * @param EquipmentGuid 装备GUID
	 */
	void RemoveEquipmentFromBackpack(int32 EquipmentGuid);

	/**
	 * @brief 从背包中出售装备
	 * @param EquipmentGuid 装备GUID
	 */
	void SellEquipmentFromBackpack(int32 EquipmentGuid);

	/**
	 * @brief 背包中是否有指定Tid的装备
	 * @param EquipmentTid 装备Tid
	 * @return 是否指定Tid的装备
	 */
	bool HasEquipmentInBackpack(int32 EquipmentTid) const;

	/**
	 * @brief 合成装备
	 * @param SynthTid 合成Tid
	 * @return 合成是否成功
	 */
	bool SynthEquipmentInBackpack(int32 SynthTid);
	
	/**
	 * @brief 获取玩家身上的道具数据
	 * @return 玩家身上的道具数据
	 */
	FORCEINLINE const TArray<FBackpackSlotData>& GetItemDatas() const
	{
		return ItemDatas;
	}

	/**
	 * @brief 添加道具到背包
	 * @param ItemTid 道具Tid
	 */
	void AddItemToBackpack(int32 ItemTid);

	/**
	 * @brief 将装备从背包中移除
	 * @param ItemGuid 装备GUID
	 * @param bRemoveAll 是否移除所有
	 */
	void RemoveItemFromBackpack(int32 ItemGuid, bool bRemoveAll = false);

	/**
	 * @brief 从背包中出售道具
	 * @param ItemGuid 道具GUID
	 */
	void SellItemFromBackpack(int32 ItemGuid);

public:
	/**
	 * @brief 金币变化回调
	 */
	UPROPERTY()
	FOnHeroStateChangeSignatureI OnCoinChange;
	
protected:
	
	/**
	 * @brief 复制玩家状态
	 * @param PlayerState 被复制的状态
	 */
	virtual void CopyProperties(APlayerState* PlayerState) override;

	/**
	 * @brief 重置
	 */
	virtual void Reset() override;

private:
	/**
	 * @brief 玩家获的金币数量
	 */
	int32 Coin = 2000;

	/**
	 * @brief 玩家身上的装备列表
	 */
	TArray<FBackpackSlotData> EquipmentDatas;

	/**
	 * @brief 玩家身上的道具列表
	 */
	TArray<FBackpackSlotData> ItemDatas;
};
