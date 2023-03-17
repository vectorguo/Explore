// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWindowWidget.h"

#include "ShopCommodityWidget.h"
#include "WindowWidgetManager.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/Hero/MainHeroState.h"
#include "Explore/Table/TableShop.h"

UShopWindowWidget::UShopWindowWidget()
{
	WindowID = EWindowWidgetID::EWWT_Forger;
	WindowType = EWindowWidgetType::EWWT_Generic;
}

UShopWindowWidget::~UShopWindowWidget()
{
	if (const auto* Manager = UExploreGameManager::GetInstance())
	{
		if (auto* Backpack = Manager->GetMainHeroBackpack())
		{
			Backpack->OnCoinChange.RemoveDynamic(this, &UShopWindowWidget::OnCoinChange);
		}
	}
}

bool UShopWindowWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		CoinTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoinValueTxt")));
		ContainerGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("GridContainer")));
	}
	return Result;
}

void UShopWindowWidget::InitializeData(int32 InShopTid)
{
	const auto* ShopConfig = FTableShop::GetRow(InShopTid);
	if (ShopConfig == nullptr || !ShopCommodityClass)
	{
		return;
	}

	//当前金币数量
	auto CurCoin = 0;
	if (auto* Backpack = UExploreGameManager::GetInstance()->GetMainHeroBackpack())
	{
		CurCoin = Backpack->GetCoin();
		CoinTxt->SetText(FText::FromString(FString::FromInt(CurCoin)));

		//注册回调
		Backpack->OnCoinChange.AddDynamic(this, &UShopWindowWidget::OnCoinChange);
	}

	auto Index = 0;
	auto* WindowOwner = FWindowWidgetManager::GetInstance()->GetWindowOwner();
	
	//添加装备
	TArray<UShopCommodityWidget*> CommodityWidgets;
	for (auto I = 0; I < ShopConfig->Equipments.Num(); I += 2)
	{
		auto* Commodity = CreateWidget<UShopCommodityWidget>(WindowOwner, ShopCommodityClass);
		Commodity->InitializeData(ShopConfig->Equipments[I], ShopConfig->Equipments[I + 1], CurCoin, true);
		CommodityWidgets.Add(Commodity);
	}
	CommodityWidgets.Sort([](const UShopCommodityWidget& Commodity1, const UShopCommodityWidget& Commodity2)
	{
		return Commodity1.GetCommodityQuality() > Commodity2.GetCommodityQuality();
	});
	for (auto* Commodity : CommodityWidgets)
	{
		ContainerGrid->AddChildToUniformGrid(Commodity, Index / 6, Index % 6);
		++Index;
	}

	//添加道具
	CommodityWidgets.Empty();
	for (auto I = 0; I < ShopConfig->Items.Num(); I += 2)
	{
		auto* Commodity = CreateWidget<UShopCommodityWidget>(WindowOwner, ShopCommodityClass);
		Commodity->InitializeData(ShopConfig->Items[I], ShopConfig->Items[I + 1], CurCoin, false);
		CommodityWidgets.Add(Commodity);
	}
	CommodityWidgets.Sort([](const UShopCommodityWidget& Commodity1, const UShopCommodityWidget& Commodity2)
	{
		return Commodity1.GetCommodityQuality() > Commodity2.GetCommodityQuality();
	});
	for (auto* Commodity : CommodityWidgets)
	{
		ContainerGrid->AddChildToUniformGrid(Commodity, Index / 6, Index % 6);
		++Index;
	}
}

void UShopWindowWidget::OnCoinChange(int32 Coin)
{
	//刷新玩家金币显示
	CoinTxt->SetText(FText::FromString(FString::FromInt(Coin)));

	//刷新商品
	auto Children = ContainerGrid->GetAllChildren();
	for (auto* Child : Children)
	{
		if (auto* CommodityWidget = Cast<UShopCommodityWidget>(Child))
		{
			CommodityWidget->Refresh(Coin);
		}
	}
}
