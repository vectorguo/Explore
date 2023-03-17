// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHeroState.h"

#include "Explore/Table/TableEquipment.h"
#include "Explore/Table/TableEquipmentSynthesis.h"
#include "Explore/Table/TableItem.h"

void AMainHeroState::AddEquipmentToBackpack(int32 EquipmentTid)
{
	FBackpackSlotData Data(GenerateGuid(), EquipmentTid, 1, 1, true);
	EquipmentDatas.Emplace(Data);	
}

void AMainHeroState::AddEquipmentToBackpack(const FBackpackSlotData& EquipmentData)
{
	if (EquipmentDatas.ContainsByPredicate([EquipmentData](const FBackpackSlotData& Data)
	{
		return Data.Guid == EquipmentData.Guid;
	}))
	{
		return;
	}

	EquipmentDatas.Emplace(EquipmentData);
}

void AMainHeroState::RemoveEquipmentFromBackpack(int32 EquipmentGuid)
{
	auto Index = EquipmentDatas.IndexOfByPredicate([EquipmentGuid](const FBackpackSlotData& Data)
	{
		return Data.Guid == EquipmentGuid;
	});
	if (Index != INDEX_NONE)
	{
		EquipmentDatas.RemoveAtSwap(Index);
	}
}

void AMainHeroState::SellEquipmentFromBackpack(int32 EquipmentGuid)
{
	auto Index = EquipmentDatas.IndexOfByPredicate([EquipmentGuid](const FBackpackSlotData& Data)
	{
		return Data.Guid == EquipmentGuid;
	});
	if (Index != INDEX_NONE)
	{
		const auto& EquipData = EquipmentDatas[Index];

		//获取金币
		const auto* EquipConfig = FTableEquipment::GetRow(EquipData.Tid);
		AddCoin(EquipData.Count * EquipConfig->SellPrice);

		//删除装备
		EquipmentDatas.RemoveAtSwap(Index);
	}
}

bool AMainHeroState::HasEquipmentInBackpack(int32 EquipmentTid) const
{
	auto Index = EquipmentDatas.IndexOfByPredicate([EquipmentTid](const FBackpackSlotData& Data)
	{
		return Data.Tid == EquipmentTid;
	});
	return Index != INDEX_NONE;
}

bool AMainHeroState::SynthEquipmentInBackpack(int32 SynthTid)
{
	const auto* Config = FTableEquipmentSynthesis::GetRow(SynthTid);
	if (Config)
	{
		bool HasAllMaterials = true;
		for (auto Tid : Config->EquipMaterials)
		{
			if (!HasEquipmentInBackpack(Tid))
			{
				HasAllMaterials = false;
				break;
			}
		}

		if (HasAllMaterials)
		{
			//删除合成所需的材料
			for (auto Tid : Config->EquipMaterials)
			{
				EquipmentDatas.RemoveAtSwap(EquipmentDatas.IndexOfByPredicate([Tid](const FBackpackSlotData& Data)
				{
					return Data.Tid == Tid;
				}));
			}

			//添加合成的装备
			AddEquipmentToBackpack(Config->EquipmentTid);
			
			return true;		
		}
	}
	return false;
}

void AMainHeroState::AddItemToBackpack(int32 ItemTid)
{
	auto* ItemDataPointer = ItemDatas.FindByPredicate([ItemTid](const FBackpackSlotData& SlotData){return SlotData.Tid == ItemTid;});
	if (ItemDataPointer)
	{
		//检查是否可以堆叠
		const auto* ItemConfig = FTableItem::GetRow(ItemTid);
		if (ItemConfig->Stacked)
		{
			++ItemDataPointer->Count;
		}
		else
		{
			ItemDatas.Emplace(GenerateGuid(), ItemTid, -1, 1, false);
		}
	}
	else
	{
		//直接添加
		ItemDatas.Emplace(GenerateGuid(), ItemTid, -1, 1, false);
	}
}

void AMainHeroState::RemoveItemFromBackpack(int32 ItemGuid, bool bRemoveAll)
{
	auto Index = ItemDatas.IndexOfByPredicate([ItemGuid](const FBackpackSlotData& Data)
	{
		return Data.Guid == ItemGuid;
	});
	if (Index != INDEX_NONE)
	{
		if (bRemoveAll)
		{
			ItemDatas.RemoveAtSwap(Index);
		}
		else
		{
			auto& ItemData = ItemDatas[Index];
			if (--ItemData.Count == 0)
			{
				ItemDatas.RemoveAtSwap(Index);
			}
		}
	}
}

void AMainHeroState::SellItemFromBackpack(int32 ItemGuid)
{
	auto Index = ItemDatas.IndexOfByPredicate([ItemGuid](const FBackpackSlotData& Data)
	{
		return Data.Guid == ItemGuid;
	});
	if (Index != INDEX_NONE)
	{
		const auto& ItemData = ItemDatas[Index];

		//获取金币
		const auto* ItemConfig = FTableItem::GetRow(ItemData.Tid);
		AddCoin(ItemData.Count * ItemConfig->SellPrice);

		//删除装备
		ItemDatas.RemoveAtSwap(Index);
	}
}

int32 AMainHeroState::GenerateGuid()
{
	static int32 Guid = 0;
	return ++Guid;
}

void AMainHeroState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (auto* MainHeroState = Cast<AMainHeroState>(PlayerState))
	{
		MainHeroState->Coin = Coin;
	}
}

void AMainHeroState::Reset()
{
	Super::Reset();

	Coin = 0;
}
