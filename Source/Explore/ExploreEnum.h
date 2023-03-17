#pragma once

#include "CoreMinimal.h"

/**
 * @brief 角色状态类型
 */
UENUM(BlueprintType)
enum class ECharacterStateType : uint8
{
	ECS_None			UMETA(DisplayName = "None"),
	ECS_PlayerControl	UMETA(DisplayName = "PlayerControl"),
	ECS_Skill			UMETA(DisplayName = "Skill"),
	ECS_Death			UMETA(DisplayName = "Death"),

	ECS_Idle			UMETA(DisplayName = "Idle"),
	ECS_Move			UMETA(DisplayName = "Move"),
};

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	EDT_None UMETA(DisplayName = "None"),
	EDT_Normal UMETA(DisplayName = "Normal"),
	EDT_Crit UMETA(DisplayName = "Crit"),
	EDT_Miss UMETA(DisplayName = "Miss"),
};

UENUM(BlueprintType)
enum class EEquipmentPart : uint8
{
	EEP_None UMETA(DisplayName = "None"),
	EEP_Weapon UMETA(DisplayName = "Weapon"),
	EEP_Armor UMETA(DisplayName = "Armor"),
	EEP_Ring UMETA(DisplayName = "Ring"),
	EEP_Shoes UMETA(DisplayName = "Shoes"),
	EEP_Ornament UMETA(DisplayName = "Ornament"),
	EEP_Special UMETA(DisplayName = "Special"),
};

UENUM(BlueprintType)
enum class EQuality : uint8
{
	EQ_None UMETA(DisplayName = "None"),
	EQ_White UMETA(DisplayName = "White"),
	EQ_Grey UMETA(DisplayName = "Grey"),
	EQ_Green UMETA(DisplayName = "Green"),
	EQ_Blue UMETA(DisplayName = "Blue"),
	EQ_Purple UMETA(DisplayName = "Purple"),
	EQ_Yellow UMETA(DisplayName = "Yellow"),
	EQ_Orange UMETA(DisplayName = "Orange"),
	EQ_Red UMETA(DisplayName = "Red"),
};

/**
 * @brief 背包Slot上下文类型
 */
UENUM(BlueprintType)
enum class EBackpackSlotContext : uint8
{
	EBC_None UMETA(DisplayName = "None"),
	EBC_InBackpack UMETA(DisplayName = "InBackpack"),
	EBC_Worn UMETA(DisplayName = "Worn"),
	EBC_SynthResult UMETA(DisplayName = "SynthResult"),
	EBC_SynthMaterial UMETA(DisplayName = "SynthMaterial"),
	EBC_ShopCommodity UMETA(DisplayName = "ShopCommodity"),
};

/**
 * @brief 技能元素类型
 */
UENUM(BlueprintType)
enum class ECharacterElement : uint8
{
	ECE_None		UMETA(DisplayName = "None"),		//无
	ECE_Ice			UMETA(DisplayName = "Ice"),			//冰
	ECE_Fire		UMETA(DisplayName = "Fire"),		//火
	ECE_Soil		UMETA(DisplayName = "Soil"),		//土
	ECE_Thunder		UMETA(DisplayName = "Thunder"),		//雷
	ECE_Toxic		UMETA(DisplayName = "Toxic"),		//毒
	ECE_Chaotic		UMETA(DisplayName = "Chaotic"),		//混沌
};