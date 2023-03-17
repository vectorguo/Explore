// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopCommodityWidget.h"

#include "EquipmentInfoWindowWidget.h"
#include "ItemInfoWindowWidget.h"
#include "WindowWidgetManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/Hero/MainHeroState.h"
#include "Explore/Characters/Hero/MainHeroStateStruct.h"
#include "Explore/Table/TableEquipment.h"
#include "Explore/Table/TableItem.h"
#include "Explore/Utility/ExploreUtility.h"

UShopCommodityWidget::~UShopCommodityWidget()
{
}

void UShopCommodityWidget::InitializeData(int32 InTid, int32 InPrice, int32 Coin, bool bIsEquip)
{
	Tid = InTid;
	Price = InPrice;
	bIsEquipment = bIsEquip;
	
	FColor QualityColor;
	FString Name;
	FString IconPath;
	if (bIsEquip)
	{
		const auto* EquipConfig = FTableEquipment::GetRow(InTid);
		QualityColor = FExploreUtility::GetQualityColor(EquipConfig->Quality);
		Name = EquipConfig->Name;
		IconPath = EquipConfig->Icon;
	}
	else
	{
		const auto* ItemConfig = FTableItem::GetRow(InTid);
		QualityColor = FExploreUtility::GetQualityColor(ItemConfig->Quality);
		Name = ItemConfig->Name;
		IconPath = ItemConfig->Icon;
	}

	//Name
	auto* NameTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtName")));
	NameTxt->SetText(FText::FromString(Name));
	NameTxt->SetColorAndOpacity(QualityColor);
	
	//Icon
	auto* IconImg = Cast<UImage>(GetWidgetFromName(TEXT("ImgIcon")));
	if (auto* TexIcon = LoadObject<UTexture2D>(nullptr, *IconPath))
	{
		IconImg->SetBrushFromTexture(TexIcon);
	}
	
	//品质框
	auto* QualityImg = Cast<UImage>(GetWidgetFromName(TEXT("ImgQualityBg")));
	QualityColor.A = 75;
	QualityImg->SetColorAndOpacity(QualityColor);
	
	//价格
	auto* PriceTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtPrice")));
	PriceTxt->SetText(FText::FromString(FString::FromInt(InPrice)));
	if (InPrice > Coin)
	{
		PriceTxt->SetColorAndOpacity(FColor(255, 0, 0, 255));
	}
}

void UShopCommodityWidget::Refresh(int32 Coin)
{
	auto* PriceTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtPrice")));
	if (Price > Coin)
	{
		PriceTxt->SetColorAndOpacity(FColor(255, 0, 0, 255));
	}
	else
	{
		PriceTxt->SetColorAndOpacity(FColor(0, 0, 0, 255));
	}
}

int32 UShopCommodityWidget::GetCommodityQuality() const
{
	if (bIsEquipment)
	{
		const auto* EquipConfig = FTableEquipment::GetRow(Tid);
		return EquipConfig->Quality;
	}
	else
	{
		const auto* ItemConfig = FTableItem::GetRow(Tid);
		return ItemConfig->Quality;
	}
}

void UShopCommodityWidget::OnClick()
{
	if (bIsEquipment)
	{
		const FBackpackSlotData SlotData(-1, Tid, 1, -1, true);
		auto* Window = FWindowWidgetManager::GetInstance()->OpenWindow<UEquipmentInfoWindowWidget>(EWindowWidgetID::EWWT_EquipmentInfo);
		Window->InitializeData(&SlotData, EBackpackSlotContext::EBC_ShopCommodity);
	}
	else
	{
		const FBackpackSlotData SlotData(-1, Tid, 1, -1, false);
		auto* Window = FWindowWidgetManager::GetInstance()->OpenWindow<UItemInfoWindowWidget>(EWindowWidgetID::EWWT_ItemInfo);
		Window->InitializeData(&SlotData, EBackpackSlotContext::EBC_ShopCommodity);
	}
}

void UShopCommodityWidget::OnClickBuy()
{
	auto* Backpack = UExploreGameManager::GetInstance()->GetMainHeroBackpack();
	if (Price <= Backpack->GetCoin())
	{
		//购买成功
		if (bIsEquipment)
		{
			Backpack->AddEquipmentToBackpack(Tid);
		}
		else
		{
			Backpack->AddItemToBackpack(Tid);
		}
		
		//扣除金币
		Backpack->AddCoin(-Price);
	}
}
