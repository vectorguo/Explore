#pragma once

/**
 * @brief 背包道具数据
 */
struct FBackpackSlotData
{
	int32 Guid;
	int32 Tid;
	int32 Level;
	int32 Count;
	bool bIsEquipment;

	FBackpackSlotData() :
		Guid(0),
		Tid(0),
		Level(0),
		Count(0),
		bIsEquipment(false)
	{
		
	}
	
	FBackpackSlotData(int32 InGuid, int32 InTid, int32 InLevel, int32 InCount, bool bIsEquip) :
		Guid(InGuid),
		Tid(InTid),
		Level(InLevel),
		Count(InCount),
		bIsEquipment(bIsEquip)
	{
		
	}
};
