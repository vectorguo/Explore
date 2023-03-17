// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterItem.h"

#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Table/TableItem.h"


void UCharacterItem::AddItemEffect()
{
	if (HeroOwner == nullptr)
	{
		return;
	}
	
	if (const auto* ItemConfig = FTableItem::GetRow(GetItemTid()))
	{
		//添加道具附带的属性
		const auto& Attributes = ItemConfig->Attributes;
		for (auto Index = 0; Index + 1 < Attributes.Num(); Index += 2)
		{
			HeroOwner->GetAttribute()->ModifyAttributeValue(static_cast<EAttributeType>(Attributes[Index]), Attributes[Index + 1]);
		}
		
		//添加道具附带的技能效果
		for (const auto SkillID : ItemConfig->Skills)
		{
			HeroOwner->GetSkillManager()->AddSkill(SkillID);
		}

		//添加道具附带的Buff效果
		for (const auto BuffID : ItemConfig->Buffs)
		{
			auto BuffGuid = HeroOwner->GetBuffManager()->AddBuff(BuffID, HeroOwner);
			if (BuffGuid > 0)
			{
				BuffGuids.Emplace(BuffGuid);
			}
		}
	}
}

void UCharacterItem::RemoveItemEffect()
{
	if (HeroOwner == nullptr)
	{
		return;
	}

	if (const auto* EquipConfig = FTableItem::GetRow(GetItemTid()))
	{
		//删除武器附带的属性
		const auto& Attributes = EquipConfig->Attributes;
		for (auto Index = 0; Index + 1 < Attributes.Num(); Index += 2)
		{
			HeroOwner->GetAttribute()->ModifyAttributeValue(static_cast<EAttributeType>(Attributes[Index]), -Attributes[Index + 1]);
		}
		
		//删除武器附带的技能
		for (const auto SkillID : EquipConfig->Skills)
		{
			HeroOwner->GetSkillManager()->RemoveSkill(SkillID);
		}

		//删除武器附带的Buff效果
		for (auto BuffGuid : BuffGuids)
		{
			HeroOwner->GetBuffManager()->RemoveBuff(BuffGuid);
		}
		BuffGuids.Empty();
	}
}