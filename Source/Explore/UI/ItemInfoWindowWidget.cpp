// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoWindowWidget.h"

#include "BackpackSlotWidget.h"
#include "HeroInfoWindowWidget.h"
#include "WindowWidgetManager.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/Hero/MainHeroState.h"
#include "Explore/Characters/Hero/MainHeroStateStruct.h"
#include "Explore/Table/TableItem.h"
#include "Explore/Utility/ExploreUtility.h"

UItemInfoWindowWidget::UItemInfoWindowWidget()
{
	WindowID = EWindowWidgetID::EWWT_ItemInfo;
	WindowType = EWindowWidgetType::EWWT_Dialog;
}

UItemInfoWindowWidget::~UItemInfoWindowWidget()
{
}

bool UItemInfoWindowWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		ItemSlot = Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("SlotItem")));
		ItemNameTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtItemName")));
		ItemLevelTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtItemLevel")));
		ItemDescriptionTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtItemDesc")));
		SellBtnParent = Cast<USizeBox>(GetWidgetFromName(TEXT("SbSell")));
		SellBtnParent->SetVisibility(ESlateVisibility::Hidden);
		OperationBtnParent = Cast<USizeBox>(GetWidgetFromName(TEXT("SbOperation")));
		OperationBtnParent->SetVisibility(ESlateVisibility::Hidden);
		OperationNameTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtOperationName")));
	}
	return Result;
}

void UItemInfoWindowWidget::InitializeData(const FBackpackSlotData* Data, EBackpackSlotContext InContext)
{
	ItemData = Data;
	Context = InContext;

	const auto* EquipmentConfig = FTableItem::GetRow(ItemData->Tid);
	ItemSlot->InitializeData(*ItemData, EBackpackSlotContext::EBC_None);
	ItemNameTxt->SetText(FText::FromString(EquipmentConfig->Name));
	ItemNameTxt->SetColorAndOpacity(FExploreUtility::GetQualitySlateColor(EquipmentConfig->Quality));
	ItemLevelTxt->SetText(FText::FromString(TEXT("无")));
	ItemDescriptionTxt->SetText(FText::FromString(EquipmentConfig->Description));

	//显示操作按钮
	switch (Context)
	{
		case EBackpackSlotContext::EBC_InBackpack:
		{
			//检测道具是否可以使用
			const auto* ItemConfig = FTableItem::GetRow(ItemData->Tid);
			OperationBtnParent->SetVisibility(ItemConfig->Use ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
			SellBtnParent->SetVisibility(ESlateVisibility::Visible);
			break;
		}
		default:
			OperationBtnParent->SetVisibility(ESlateVisibility::Hidden);
			SellBtnParent->SetVisibility(ESlateVisibility::Hidden);
			break;
	}
}

void UItemInfoWindowWidget::OnClickOperation()
{
	switch (Context)
	{
		case EBackpackSlotContext::EBC_InBackpack:
		{
			auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
			MainHero->UseItem(ItemData);

			//刷新英雄信息界面
			if (auto* HeroInfoWindow = FWindowWidgetManager::GetInstance()->GetWindow<UHeroInfoWindowWidget>(EWindowWidgetID::EWWT_HeroInfo))
			{
				HeroInfoWindow->Refresh();
			}
		
			Close();
			break;
		}
		default:
			break;
	}
}

void UItemInfoWindowWidget::OnClickSell()
{
	auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
	auto* Backpack = MainHero->GetBackpack();
	Backpack->SellItemFromBackpack(ItemData->Guid);

	//刷新英雄信息界面
	if (auto* HeroInfoWindow = FWindowWidgetManager::GetInstance()->GetWindow<UHeroInfoWindowWidget>(EWindowWidgetID::EWWT_HeroInfo))
	{
		HeroInfoWindow->Refresh();
	}
	
	//关闭当前界面
	Close();
}
