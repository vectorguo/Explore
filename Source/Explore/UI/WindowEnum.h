#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWindowWidgetID : uint8
{
	EWWT_None				UMETA(DisplayName = "None"),			//空
	EWWT_Main				UMETA(DisplayName = "Main"),			//主窗口
	EWWT_HeroInfo			UMETA(DisplayName = "HeroInfo"),		//英雄信息
	EWWT_EquipmentInfo		UMETA(DisplayName = "EquipmentInfo"),	//装备信息
	EWWT_ItemInfo			UMETA(DisplayName = "ItemInfo"),		//道具信息
	EWWT_Forger				UMETA(DisplayName = "Forger"),			//铸造师界面（装备升级和合成）
	EWWT_Shop				UMETA(DisplayName = "Shop"),			//商店
};

UENUM(BlueprintType)
enum class EWindowWidgetType : uint8
{
	EWWT_Main UMETA(DisplayName = "Main"),			//主窗口
	EWWT_Generic UMETA(DisplayName = "Generic"),	//通用界面
	EWWT_Dialog UMETA(DisplayName = "Dialog"),		//对话框
};
