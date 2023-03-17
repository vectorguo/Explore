// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttribute.h"

void UCharacterAttribute::Initialize()
{
	UpdateAttack();
	UpdateArmor();
}

void UCharacterAttribute::ModifyHealth(float DeltaValue)
{
	if (DeltaValue == 0)
	{
		return;
	}

	Health += DeltaValue;
	
	float Delta = DeltaValue;
	if (DeltaValue < 0 && Health < 0)
	{
		Delta -= Health;
		Health = 0;
	}
	else if (DeltaValue > 0 && Health > MaxHealth)
	{
		Delta -= Health - MaxHealth;
		Health = MaxHealth;
	}

	//触发回调
	OnHealthChange.Broadcast(this, Health, Delta);
}

void UCharacterAttribute::ModifyMaxHealth(float DeltaValue)
{
	if (DeltaValue == 0)
	{
		return;
	}

	const auto OriMaxHealth = MaxHealth;
	MaxHealth += DeltaValue;
	if (DeltaValue > 0)
	{
		//最大血量增加
		OnMaxHealthChange.Broadcast(this, MaxHealth, DeltaValue);

		//修改当前血量
		const auto NewHealth = Health / OriMaxHealth * MaxHealth;
		DeltaValue = NewHealth - Health;
		Health = NewHealth;
		OnHealthChange.Broadcast(this, Health, DeltaValue);
	}
	else
	{
		//最大血量减少
		if (MaxHealth <= 1)
		{
			MaxHealth = 1;
			DeltaValue = MaxHealth - OriMaxHealth;
		}
		OnMaxHealthChange.Broadcast(this, MaxHealth, DeltaValue);

		//修改当前血量
		if (Health > MaxHealth)
		{
			DeltaValue = MaxHealth - Health;
			Health = MaxHealth;
			OnHealthChange.Broadcast(this, Health, DeltaValue);
		}
	}
}

float UCharacterAttribute::GetAttributeValue(EAttributeType AttrType) const
{
	switch (AttrType)
	{
		case EAttributeType::EAT_Strength:
			return Strength;
		case EAttributeType::EAT_ExtraStrength:
			return ExtraStrength;
		case EAttributeType::EAT_Agility:
			return Agility;
		case EAttributeType::EAT_ExtraAgility:
			return ExtraAgility;
		case EAttributeType::EAT_Intelligence:
			return Intelligence;
		case EAttributeType::EAT_ExtraIntelligence:
			return ExtraIntelligence;
		case EAttributeType::EAT_Health:
			return Health;
		case EAttributeType::EAT_MaxHealth:
			return MaxHealth;
		case EAttributeType::EAT_Attack:
			return Attack;
		case EAttributeType::EAT_ExtraAttack:
			return PureAttack;
		case EAttributeType::EAT_Armor:
			return Armor;
		case EAttributeType::EAT_ExtraArmor:
			return PureArmor;
		case EAttributeType::EAT_CritRate:
			return CritRate;
		case EAttributeType::EAT_CritMultiple:
			return CritMultiple;
		case EAttributeType::EAT_DamageIncrease:
			return DamageIncreaseRatio;
		case EAttributeType::EAT_DamageDecrease:
			return DamageDecreaseRatio;
		case EAttributeType::EAT_DamageBlock:
			return DamageBlock;
		case EAttributeType::EAT_BloodAbsorbing:
			return BloodAbsorbingRatio;
		case EAttributeType::EAT_MovementSpeed:
			return MovementSpeed;
		case EAttributeType::EAT_SkillSpeed:
			return SkillSpeed;
		case EAttributeType::EAT_Level:
			return Level;
		case EAttributeType::EAT_Experience:
			return Experience;
		case EAttributeType::EAT_ReviveTime:
			return ReviveTime;
		case EAttributeType::EAT_ElementIce:
			return ElementIce;
		case EAttributeType::EAT_ElementFire:
			return ElementFire;
		case EAttributeType::EAT_ElementSoil:
			return ElementSoil;
		case EAttributeType::EAT_ElementThunder:
			return ElementThunder;
		case EAttributeType::EAT_ElementToxic:
			return ElementToxic;
		case EAttributeType::EAT_ElementChaotic:
			return ElementChaotic;
		default:
			return 0;
	}
}

void UCharacterAttribute::ModifyAttributeValue(EAttributeType AttrType, float DeltaValue)
{
	switch (AttrType)
	{
		case EAttributeType::EAT_Strength:
			//不能被修改
			break;
		case EAttributeType::EAT_ExtraStrength:
			ExtraStrength += DeltaValue;
			UpdateStrength();
			break;
		case EAttributeType::EAT_Agility:
			//不能被修改
			break;
		case EAttributeType::EAT_ExtraAgility:
			Agility += DeltaValue;
			UpdateAgility();
			break;
		case EAttributeType::EAT_Intelligence:
			//不能被修改
			break;
		case EAttributeType::EAT_ExtraIntelligence:
			Intelligence += DeltaValue;
			UpdateIntelligence();
			break;
		case EAttributeType::EAT_Health:
			ModifyHealth(DeltaValue);
			break;
		case EAttributeType::EAT_MaxHealth:
			ModifyMaxHealth(DeltaValue);
			break;
		case EAttributeType::EAT_Attack:
			//不能被修改
			break;
		case EAttributeType::EAT_ExtraAttack:
			ModifyExtraAttack(DeltaValue);
			break;
		case EAttributeType::EAT_Armor:
			//不能被修改
			break;
		case EAttributeType::EAT_ExtraArmor:
			ModifyExtraArmor(DeltaValue);
			break;
		case EAttributeType::EAT_CritRate:
			CritRate += DeltaValue;
			break;
		case EAttributeType::EAT_CritMultiple:
			CritMultiple += DeltaValue;
			break;
		case EAttributeType::EAT_DamageIncrease:
			DamageIncreaseRatio += DeltaValue;
			break;
		case EAttributeType::EAT_DamageDecrease:
			DamageDecreaseRatio += DeltaValue;
			break;
		case EAttributeType::EAT_DamageBlock:
			DamageBlock += DeltaValue;
			break;
		case EAttributeType::EAT_BloodAbsorbing:
			BloodAbsorbingRatio += DeltaValue;
			break;
		case EAttributeType::EAT_SkillSpeed:
			SkillSpeed += DeltaValue;
			break;
		case EAttributeType::EAT_Level:
			//不能被修改
			break;
		case EAttributeType::EAT_Experience:
			Experience += DeltaValue;
			OnExperienceChange.Broadcast(this, Experience);
			break;
		case EAttributeType::EAT_ElementIce:
			//冰元素
			ElementIce += DeltaValue;
			break;
		case EAttributeType::EAT_ElementFire:
			//火元素
			ElementFire += DeltaValue;
			break;
		case EAttributeType::EAT_ElementSoil:
			//土元素
			ElementSoil += DeltaValue;
			break;
		case EAttributeType::EAT_ElementThunder:
			//雷元素
			ElementThunder += DeltaValue;
			break;
		case EAttributeType::EAT_ElementToxic:
			//毒元素
			ElementToxic += DeltaValue;
			break;
		case EAttributeType::EAT_ElementChaotic:
			//混沌元素
			ElementChaotic += DeltaValue;
			break;
		case EAttributeType::EAT_ElementAll:
			//所有元素
			ElementIce += DeltaValue;
			ElementFire += DeltaValue;
			ElementSoil += DeltaValue;
			ElementThunder += DeltaValue;
			ElementToxic += DeltaValue;
			ElementChaotic += DeltaValue;
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("未实现属性%d的修改函数"), static_cast<int>(AttrType));
	}
}

void UCharacterAttribute::Reset()
{
	Health = MaxHealth;

	//触发回调
	OnHealthChange.Broadcast(this, Health, 0);
}