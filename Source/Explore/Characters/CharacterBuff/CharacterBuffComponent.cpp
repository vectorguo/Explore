// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBuffComponent.h"

#include "CharacterBuff_Attribute.h"
#include "CharacterBuffBase.h"
#include "CharacterBuff_AddBuffToTargetBeforeAtk.h"
#include "CharacterBuff_DamageAfterAtk.h"
#include "CharacterBuff_HealthRecovery.h"
#include "CharacterBuff_Thunder3000.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Table/TableBuff.h"


// Sets default values for this component's properties
UCharacterBuffComponent::UCharacterBuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//
	Owner = Cast<AExploreCharacter>(GetOwner());
}

// Called every frame
void UCharacterBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//更新Buff
	for (auto Iter = Buffs.CreateIterator(); Iter; ++Iter)
	{
		auto* Buff = *Iter;
		Buff->Tick(DeltaTime);
		if (Buff->GetBuffState() == EBuffState::EBS_Finished)
		{
			Iter.RemoveCurrent();
		}
	}
}

int32 UCharacterBuffComponent::AddBuff(int32 BuffTid, AExploreCharacter* Causer)
{
	const auto* Buff = CreateBuff(BuffTid, Causer);
	return Buff ? Buff->GetGUID() : -1;
}

void UCharacterBuffComponent::RemoveBuff(int32 BuffGuid)
{
	auto Index = Buffs.IndexOfByPredicate([BuffGuid](const UCharacterBuffBase* Buff)
	{
		return Buff->GetGUID() == BuffGuid;
	});
	if (Index != INDEX_NONE)
	{
		Buffs[Index]->Destroy(false);
		Buffs.RemoveAtSwap(Index);
	}
}

void UCharacterBuffComponent::InvokeBuffBeforeAtk(AExploreCharacter* Target)
{
	for (auto* Buff : Buffs)
	{
		if (Buff->GetBuffType() == EBuffType::EBT_BeforeAttack)
		{
			Buff->TakeEffectBeforeAtk(Target);
		}
	}
}

void UCharacterBuffComponent::InvokeBuffAfterAtk(AExploreCharacter* Target)
{
	for (auto* Buff : Buffs)
	{
		if (Buff->GetBuffType() == EBuffType::EBT_AfterAttack)
		{
			Buff->TakeEffectAfterAtk(Target);
		}
	}
}

UCharacterBuffBase* UCharacterBuffComponent::CreateBuff(int32 BuffTid, AExploreCharacter* Causer)
{
	static int32 BuffGuid = 0;
	
	const auto* BuffConfig = FTableBuff::GetRow(BuffTid);
	if (BuffConfig == nullptr)
	{
		return nullptr;
	}

	//处理Buff替换
	switch (BuffConfig->ReplacementRule)
	{
		case 1:
			//替换掉相同Group的Buff
			RemoveBuffsByGroup(BuffConfig->Group);
			break;
		default:
			break;
	}
	
	UCharacterBuffBase* Buff;
	switch (BuffConfig->Kind)
	{
		case 1:
			//属性Buff
			Buff = NewObject<UCharacterBuff_Attribute>(Owner);
			break;
		case 10:
			//回血Buff
			Buff = NewObject<UCharacterBuff_HealthRecovery>(Owner);
			break;
		case 100:
			//攻击前添加Buff到目标身上的Buff
			Buff = NewObject<UCharacterBuff_AddBuffToTargetBeforeAtk>(Owner);
			break;
		case 103:
			//攻击后对目标造成单体/范围伤害的Buff
			Buff = NewObject<UCharacterBuff_DamageAfterAtk>(Owner);
			break;
		case 3000:
			//五雷轰顶Buff
			Buff = NewObject<UCharacterBuff_Thunder3000>(Owner);
			break;
		default:
			return nullptr;
	}

	Buff->Initialize(++BuffGuid, Owner, Causer, BuffConfig);
	
	if (Buff->GetBuffType() == EBuffType::EBT_Attribute ||
		Buff->GetBuffType() == EBuffType::EBT_Status ||
		Buff->GetBuffType() == EBuffType::EBT_ChangingAttribute)
	{
		//属性类Buff和状态类Buff添加时立即生效
		Buff->TakeEffect();
	}
	Buffs.Emplace(Buff);
	return Buff;
}

void UCharacterBuffComponent::RemoveBuffsByGroup(int32 BuffGroup)
{
	for (auto Iter = Buffs.CreateIterator(); Iter; ++Iter)
	{
		auto* Buff = *Iter;
		if (Buff->GetBuffGroup() == BuffGroup)
		{
			Buff->Destroy(false);
			Iter.RemoveCurrent();
		}
	}
}

