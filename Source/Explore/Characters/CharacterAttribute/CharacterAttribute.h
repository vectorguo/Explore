// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Explore/ExploreEnum.h"
#include "UObject/Object.h"
#include "CharacterAttribute.generated.h"

class UCharacterAttribute;

//声明一个动态广播委托
//第一个参数事件的名称（自己定义）
//后面的参数是事件所需要的参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangeSignature21, UCharacterAttribute*, Attribute, float, Value);

//声明一个动态广播委托
//第一个参数事件的名称（自己定义）
//后面的参数是事件所需要的参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChangeSignature22, UCharacterAttribute*, Attribute, int32, Value);

//声明一个动态广播委托
//第一个参数事件的名称（自己定义）
//后面的参数是事件所需要的参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangeSignature31, UCharacterAttribute*, Attribute, float, Health, float, HealthDelta);

UENUM(BlueprintType)
enum class EAttributeType : uint8
{
	EAT_None				UMETA(DisplayName = "None"),
	EAT_Level				UMETA(DisplayName = "Level"),
	EAT_Experience			UMETA(DisplayName = "Experience"),
	EAT_Strength			UMETA(DisplayName = "Strength"),
	EAT_ExtraStrength		UMETA(DisplayName = "ExtraStrength"),
	EAT_Agility				UMETA(DisplayName = "Agility"),
	EAT_ExtraAgility		UMETA(DisplayName = "ExtraAgility"),
	EAT_Intelligence		UMETA(DisplayName = "Intelligence"),
	EAT_ExtraIntelligence	UMETA(DisplayName = "ExtraIntelligence"),
	EAT_Health				UMETA(DisplayName = "Health"),
	EAT_MaxHealth			UMETA(DisplayName = "MaxHealth"),
	EAT_Attack				UMETA(DisplayName = "Attack"),
	EAT_ExtraAttack			UMETA(DisplayName = "ExtraAttack"),
	EAT_Armor				UMETA(DisplayName = "Armor"),
	EAT_ExtraArmor			UMETA(DisplayName = "ExtraArmor"),
	EAT_CritRate			UMETA(DisplayName = "CritRate"),
	EAT_CritMultiple		UMETA(DisplayName = "CritMultiple"),
	EAT_DamageIncrease		UMETA(DisplayName = "DamageIncrease"),
	EAT_DamageDecrease		UMETA(DisplayName = "DamageDecrease"),
	EAT_BloodAbsorbing  	UMETA(DisplayName = "BloodAbsorbing"),
	EAT_MovementSpeed		UMETA(DisplayName = "MovementSpeed"),
	EAT_SkillSpeed			UMETA(DisplayName = "SkillSpeed"),
	EAT_ReviveTime			UMETA(DisplayName = "ReviveTime"),
	EAT_DamageBlock			UMETA(DisplayName = "DamageBlock"),

	EAT_ElementIce = 101	UMETA(DisplayName = "ElementIce"),
	EAT_ElementFire			UMETA(DisplayName = "ElementFire"),
	EAT_ElementSoil			UMETA(DisplayName = "ElementSoil"),
	EAT_ElementThunder		UMETA(DisplayName = "ElementThunder"),
	EAT_ElementToxic		UMETA(DisplayName = "ElementToxic"),
	EAT_ElementChaotic		UMETA(DisplayName = "ElementChaotic"),
	EAT_ElementAll = 120	UMETA(DisplayName = "ElementAll"),
};

/**
 * 角色属性
 */
UCLASS(Blueprintable)
class EXPLORE_API UCharacterAttribute : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * @brief 初始化
	 */
	void Initialize();

	/**
	 * @brief 获取等级
	 * @return 等级
	 */
	FORCEINLINE int32 GetLevel() const
	{
		return Level;
	}

	/**
	 * @brief 设置等级
	 * @param NewLevel 等级
	 */
	void SetLevel(int32 NewLevel)
	{
		if (Level == NewLevel)
		{
			return;
		}

		//更新最大血量
		const auto DeltaLevel = NewLevel - Level;
		ModifyMaxHealth(DeltaLevel * 150);
		
		//更新属性
		Level = NewLevel;
		UpdateStrength();
		UpdateAgility();
		UpdateIntelligence();

		//触发回调
		OnLevelChange.Broadcast(this, Level);
	}

	/**
	 * @brief 获取经验
	 * @return 经验
	 */
	FORCEINLINE int32 GetExperience() const
	{
		return Experience;
	}

	/**
	 * @brief 设置经验值
	 * @param NewExperience 新经验值
	 */
	void SetExperience(int32 NewExperience)
	{
		Experience = NewExperience;
		OnExperienceChange.Broadcast(this, Experience);
	}
	
	/**
	 * @brief 获取力量属性
	 * @return 力量属性值
	 */
	FORCEINLINE float GetStrength() const
	{
		return Strength;
	}

	/**
	 * @brief 获取敏捷属性
	 * @return 敏捷属性值
	 */
	FORCEINLINE float GetAgility() const
	{
		return Agility;
	}

	/**
	 * @brief 获取智力属性
	 * @return 智力属性值
	 */
	FORCEINLINE float GetIntelligence() const
	{
		return Intelligence;
	}
	
	/**
	 * @brief 获取当前血量
	 * @return 血量
	 */
	FORCEINLINE float GetHealth() const
	{
		return Health;
	}

	/**
	 * @brief 获取当前血量百分比
	 * @return 血量百分比
	 */
	FORCEINLINE float GetHealthPercent() const
	{
		return Health / MaxHealth;
	}

	/**
	 * @brief 修改血量
	 * @param DeltaValue 血量变化值
	 */
	void ModifyHealth(float DeltaValue);
	
	/**
	 * @brief 设置当前血量
	 * @param DeltaValue 当前血量
	 */
	FORCEINLINE void SetHealth(float DeltaValue)
	{
		Health = DeltaValue;
	}
	
	/**
	 * @brief 获取最大血量
	 * @return 最大血量
	 */
	FORCEINLINE float GetMaxHealth() const
	{
		return MaxHealth;
	}

	/**
	 * @brief 修改血量
	 * @param DeltaValue 最大血量变化值
	 */
	void ModifyMaxHealth(float DeltaValue);

	/**
	 * @brief 获取物理攻击力
	 * @return 物理攻击力
	 */
	FORCEINLINE float GetAttackValue() const
	{
		return Attack;
	}

	/**
	 * @brief 修改额外攻击力
	 * @param DeltaValue 额外攻击力变化值
	 */
	FORCEINLINE void ModifyExtraAttack(float DeltaValue)
	{
		PureAttack += DeltaValue;

		UpdateAttack();
	}

	/**
	 * @brief 获取物理防御力
	 * @return 物理防御力
	 */
	FORCEINLINE float GetArmorValue() const
	{
		return Armor;
	}

	/**
	 * @brief 修改额外防御值
	 * @param DeltaValue 额外防御变化值
	 */
	FORCEINLINE void ModifyExtraArmor(float DeltaValue)
	{
		PureArmor += DeltaValue;
		UpdateArmor();
	}

	/**
	 * @brief 获取指定元素类型的元素值
	 * @param ElementType 元素类型
	 * @return 元素值
	 */
	float GetElementValue(ECharacterElement ElementType) const
	{
		switch (ElementType)
		{
			case ECharacterElement::ECE_Ice:
				return ElementIce;
			case ECharacterElement::ECE_Fire:
				return ElementFire;
			case ECharacterElement::ECE_Soil:
				return ElementSoil;
			case ECharacterElement::ECE_Thunder:
				return ElementThunder;
			case ECharacterElement::ECE_Toxic:
				return ElementToxic;
			case ECharacterElement::ECE_Chaotic:
				return ElementChaotic;
			default:
				return 1.0f;
		}
	}
	
	/**
	 * @brief 根据属性类型获取对应的属性值
	 * @param AttrType 属性类型
	 * @return 属性值
	 */
	float GetAttributeValue(EAttributeType AttrType) const;

	/**
	 * @brief 根据属性类型修改对应的属性值
	 * @param AttrType 属性类型
	 * @param DeltaValue 属性变化值
	 */
	void ModifyAttributeValue(EAttributeType AttrType, float DeltaValue);
	
	/**
	 * @brief 重置
	 */
	void Reset();

private:
	/**
	 * @brief 更新力量属性
	 */
	FORCEINLINE void UpdateStrength()
	{
		Strength = Level * 5 + ExtraStrength;
		UpdateAttack();
	}

	/**
	 * @brief 更新敏捷属性
	 */
	FORCEINLINE void UpdateAgility()
	{
		Agility = Level * 5 + ExtraAgility;
		UpdateArmor();
	}

	/**
	 * @brief 更新智力属性
	 */
	FORCEINLINE void UpdateIntelligence()
	{
		Intelligence = Level * 5 + ExtraIntelligence;
	}
	
	/**
	 * @brief 更新攻击力
	 */
	FORCEINLINE void UpdateAttack()
	{
		Attack = Strength * 2 + PureAttack;
	}

	/**
	 * @brief 更新护甲
	 */
	FORCEINLINE void UpdateArmor()
	{
		Armor = Agility / 3 + PureArmor;
	}

public:
	/**
	 * @brief 血量变化回调
	 */
	UPROPERTY()
	FOnAttributeChangeSignature31 OnHealthChange;

	/**
	 * @brief 最大血量变化回调
	 */
	UPROPERTY()
	FOnAttributeChangeSignature31 OnMaxHealthChange;

	/**
	 * @brief 经验变化回调
	 */
	UPROPERTY()
	FOnAttributeChangeSignature21 OnExperienceChange;

	/**
	 * @brief 等级变化回调
	 */
	UPROPERTY()
	FOnAttributeChangeSignature22 OnLevelChange;
	
protected:
	/**
	 * @brief 等级
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	int32 Level = 1;

	/**
	 * @brief 经验
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	int32 Experience = 0;
	
	/**
	 * @brief 力量属性（额外力量属性+等级累加的力量属性）
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute")
	float Strength;

	/**
	 * @brief 额外力量属性
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ExtraStrength;

	/**
	 * @brief 敏捷属性（额外敏捷属性+等级累加的敏捷属性）
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute")
	float Agility;

	/**
	 * @brief 额外力量属性
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ExtraAgility;

	/**
	 * @brief 智力属性（额外智力属性+等级累加的智力属性）
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute")
	float Intelligence;

	/**
	 * @brief 额外力量属性
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ExtraIntelligence;

	/**
	 * @brief 当前血量
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float Health;

	/**
	 * @brief 最大血量
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float MaxHealth;

	/**
	 * @brief 攻击力(由纯攻击力和武力属性叠加得到)
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute")
	float Attack;

	/**
	 * @brief 纯攻击力
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float PureAttack;

	/**
	 * @brief 护甲(由纯护甲值和敏捷属性叠加得到)
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute")
	float Armor;

	/**
	 * @brief 纯护甲值
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float PureArmor;

	/**
	 * @brief 暴击概率
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float CritRate = 0.0f;

	/**
	 * @brief 暴击倍数
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float CritMultiple = 1.0f;

	/**
	 * @brief 伤害加成系数
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float DamageIncreaseRatio = 0.0f;

	/**
	 * @brief 伤害减免系数
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float DamageDecreaseRatio = 0.0f;

	/**
	 * @brief 伤害格挡值
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float DamageBlock = 0.0f;

	/**
	 * @brief 吸血系数
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float BloodAbsorbingRatio = 0.0f;

	/**
	 * @brief 移动速度
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float MovementSpeed = 100.0f;
	
	/**
	 * @brief 技能速度
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float SkillSpeed = 100.0f;

	/**
	 * @brief 复活时间
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ReviveTime = 5.0f;

	/**
	 * @brief 冰元素值
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ElementIce = 1.0f;

	/**
	 * @brief 火元素值
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ElementFire = 1.0f;

	/**
	 * @brief 土元素值
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ElementSoil = 1.0f;

	/**
	 * @brief 雷元素值
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ElementThunder = 1.0f;

	/**
	 * @brief 毒元素值
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ElementToxic = 1.0f;

	/**
	 * @brief 混沌元素值
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attribute")
	float ElementChaotic = 1.0f;
};
