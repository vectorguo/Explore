// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipment.h"

#include "CharacterEquipmentFacade.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/CharacterAttribute/CharacterAttribute.h"
#include "Explore/Table/TableEquipment.h"


void UCharacterEquipment::CreateFacade()
{
	const auto* EquipConfig = FTableEquipment::GetRow(GetEquipmentTid());
	if (EquipConfig == nullptr || !EquipConfig->HasFacade)
	{
		return;
	}
	
	UObject* EquipFacadeObj = StaticLoadObject(UBlueprint::StaticClass(), nullptr, *EquipConfig->FacadePath);  
    if (EquipFacadeObj != nullptr)  
    {
        auto* EquipFacadeBP = Cast<UBlueprint>(EquipFacadeObj);
    	EquipmentFacade = GetWorld()->SpawnActor<ACharacterEquipmentFacade>(EquipFacadeBP->GeneratedClass, FVector::ZeroVector, FRotator::ZeroRotator);
    	if (EquipmentFacade)
    	{
    		EquipmentFacade->SetHeroOwner(HeroOwner);
    		
    		//将武器挂在到角色身上
    		FName SocketName(*EquipConfig->SocketName);
    		if (const auto* Socket = HeroOwner->GetMesh()->GetSocketByName(SocketName))
    		{
    			Socket->AttachActor(EquipmentFacade, HeroOwner->GetMesh());
				EquipmentFacade->SetActorRelativeScale3D(FVector::OneVector);
    		}
    	}
    }
}

void UCharacterEquipment::DestroyFacade()
{
	if (EquipmentFacade)
	{
		EquipmentFacade->Destroy();
	}
}

void UCharacterEquipment::AddEquipmentEffect()
{
	if (HeroOwner == nullptr)
	{
		return;
	}
	
	if (const auto* EquipConfig = FTableEquipment::GetRow(GetEquipmentTid()))
	{
		//添加武器附带的属性
		const auto& Attributes = EquipConfig->Attributes;
		for (auto Index = 0; Index + 1 < Attributes.Num(); Index += 2)
		{
			HeroOwner->GetAttribute()->ModifyAttributeValue(static_cast<EAttributeType>(Attributes[Index]), Attributes[Index + 1]);
		}
		
		//添加武器附带的技能效果
		for (const auto SkillID : EquipConfig->Skills)
		{
			HeroOwner->GetSkillManager()->AddSkill(SkillID);
		}

		//添加武器附带的Buff效果
		for (const auto BuffID : EquipConfig->Buffs)
		{
			auto BuffGuid = HeroOwner->GetBuffManager()->AddBuff(BuffID, HeroOwner);
			if (BuffGuid > 0)
			{
				BuffGuids.Emplace(BuffGuid);
			}
		}
	}
}

void UCharacterEquipment::RemoveEquipmentEffect()
{
	if (HeroOwner == nullptr)
	{
		return;
	}

	if (const auto* EquipConfig = FTableEquipment::GetRow(GetEquipmentTid()))
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