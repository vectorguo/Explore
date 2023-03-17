// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBuff_Attribute.h"

#include "Explore/Characters/ExploreCharacter.h"

void UCharacterBuff_Attribute::Initialize(int32 InGuid, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser, const FTableBuffRowData* BuffConfig)
{
	Super::Initialize(InGuid, BuffOwner, BuffCauser, BuffConfig);

	AttributeType = static_cast<EAttributeType>(BuffConfig->Params[0]);
	DeltaValue = BuffConfig->Params[1];
}

void UCharacterBuff_Attribute::TakeEffect()
{
	Super::TakeEffect();
	
	//修改属性
	Owner->GetAttribute()->ModifyAttributeValue(AttributeType, DeltaValue);
}

void UCharacterBuff_Attribute::Destroy(bool bNormal)
{
	Super::Destroy(bNormal);
	
	//还原属性
	Owner->GetAttribute()->ModifyAttributeValue(AttributeType, -DeltaValue);
}
