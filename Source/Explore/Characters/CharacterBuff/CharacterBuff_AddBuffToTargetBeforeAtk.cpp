// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBuff_AddBuffToTargetBeforeAtk.h"

#include "Explore/Characters/ExploreCharacter.h"

void UCharacterBuff_AddBuffToTargetBeforeAtk::Initialize(int32 ID, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser, const FTableBuffRowData* BuffConfig)
{
	Super::Initialize(ID, BuffOwner, BuffCauser, BuffConfig);
	
	//记录攻击目标时要给目标添加的buff
	for (auto Tid : BuffConfig->Params)
	{
		BuffTIDs.Emplace(Tid);
	}
}

void UCharacterBuff_AddBuffToTargetBeforeAtk::TakeEffectBeforeAtk(AExploreCharacter* Target)
{
	Super::TakeEffectBeforeAtk(Target);

	if (Target)
	{
		for (auto BuffTid : BuffTIDs)
		{
			Target->GetBuffManager()->AddBuff(BuffTid, Owner);
		}
	}
}
