// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Explore/ExploreEnum.h"
#include "Explore/Characters/Hero/MainHeroStateStruct.h"
#include "UObject/Object.h"
#include "CharacterEquipment.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UCharacterEquipment : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief 显示外观
	 */
	void CreateFacade();

	/**
	 * @brief 删除外观
	 */
	void DestroyFacade();

	/**
	 * @brief 获取武器外观
	 */
	FORCEINLINE class ACharacterEquipmentFacade* GetWeaponFacade() const
	{
		return EquipmentFacade;
	}

	/**
	 * @brief 添加装备效果
	 */
	void AddEquipmentEffect();

	/**
	 * @brief 移除装备效果
	 */
	void RemoveEquipmentEffect();

	/**
	 * @brief 获取持有该武器的角色
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
	 * @brief 获取装备数据
	 * @return 装备数据
	 */
	FORCEINLINE const FBackpackSlotData& GetEquipmentData() const
	{
		return EquipmentData;
	}
	
	/**
	 * @brief 获取武器装备GUID
	 * @return 武器装备GUID
	 */
	FORCEINLINE int32 GetEquipmentGuid() const
	{
		return EquipmentData.Guid;
	}
	
	/**
	 * @brief 获取武器装备ID
	 * @return 武器装备ID
	 */
	FORCEINLINE int32 GetEquipmentTid() const
	{
		return EquipmentData.Tid;
	}

	/**
	 * @brief 设置武器装备数据
	 * @param EquipData 装备数据
	 */
	FORCEINLINE void SetEquipmentData(const FBackpackSlotData* EquipData)
	{
		EquipmentData = *EquipData;
	}
	
	/**
	 * @brief 获取武器装备的部位
	 * @return 武器装备的部位
	 */
	FORCEINLINE EEquipmentPart GetEquipmentPart() const
	{
		return EquipmentPart;
	}

	/**
	 * @brief 设置武器装备部位
	 * @param Part 武器装备部位
	 */
	FORCEINLINE void SetEquipmentPart(EEquipmentPart Part)
	{
		EquipmentPart = Part;
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
	FBackpackSlotData EquipmentData;

	/**
	 * @brief 装备附带的Buff的GUID列表
	 */
	UPROPERTY()
	TArray<int32> BuffGuids;

	/**
	 * @brief 武器装备的部位
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Property")
	EEquipmentPart EquipmentPart = EEquipmentPart::EEP_None;

	/**
	 * @brief 装备的外观
	 */
	UPROPERTY()
	class ACharacterEquipmentFacade* EquipmentFacade = nullptr;
};
