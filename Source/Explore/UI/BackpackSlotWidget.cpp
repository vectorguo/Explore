// Fill out your copyright notice in the Description page of Project Settings.


#include "BackpackSlotWidget.h"

#include "EquipmentInfoWindowWidget.h"
#include "ItemInfoWindowWidget.h"
#include "WindowWidgetManager.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Explore/Characters/Hero/MainHeroStateStruct.h"
#include "Explore/Table/TableEquipment.h"
#include "Explore/Table/TableItem.h"
#include "Explore/Utility/ExploreUtility.h"

UBackpackSlotWidget::~UBackpackSlotWidget()
{
	if (SlotData)
	{
		delete SlotData;
	}
}

bool UBackpackSlotWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		if (const auto* World = GetWorld())
		{
			Result = World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE;
			if (Result)
			{
				QualityImg = Cast<UImage>(GetWidgetFromName(TEXT("ImgQualityBg")));
				QualityImg->SetVisibility(ESlateVisibility::Hidden);
				IconImg = Cast<UImage>(GetWidgetFromName(TEXT("ImgIcon")));
				IconImg->SetVisibility(ESlateVisibility::Hidden);
				CountTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtCount")));
				CountTxt->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		
	}
	return Result;
}

void UBackpackSlotWidget::InitializeData(const FBackpackSlotData& Data, EBackpackSlotContext InContext)
{
	ClearData();
	SlotData = new FBackpackSlotData(Data);
	Context = InContext;

	//数量
	if (Data.Count >= 0)
	{
		CountTxt->SetText(FText::FromString(FString::FromInt(Data.Count)));
		CountTxt->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		CountTxt->SetVisibility(ESlateVisibility::Hidden);
	}
	
	
	FColor QualityColor;
	FString IconPath;
	if (Data.bIsEquipment)
	{
		const auto* EquipConfig = FTableEquipment::GetRow(Data.Tid);
		IconPath = EquipConfig->Icon;

		//品质框
		QualityColor = FExploreUtility::GetQualityColor(EquipConfig->Quality);
		QualityColor.A = EquipConfig->Quality <= 1 ? 0 : 100;
	}
	else
	{
		const auto* ItemConfig = FTableItem::GetRow(Data.Tid);
		IconPath = ItemConfig->Icon;

		//品质框
		QualityColor = FExploreUtility::GetQualityColor(ItemConfig->Quality);
		QualityColor.A = ItemConfig->Quality <= 1 ? 0 : 100;
	}

	//加载图片
	QualityImg->SetVisibility(ESlateVisibility::Visible);
	QualityImg->SetColorAndOpacity(QualityColor);

	if (auto* TexIcon = LoadObject<UTexture2D>(nullptr, *IconPath))
	{
		IconImg->SetBrushFromTexture(TexIcon);
		IconImg->SetVisibility(ESlateVisibility::Visible);
	}
}

void UBackpackSlotWidget::ClearData()
{
	if (SlotData == nullptr)
	{
		return;
	}
	delete SlotData;
	SlotData = nullptr;

	IconImg->SetBrushFromTexture(nullptr);
	IconImg->SetVisibility(ESlateVisibility::Hidden);
	QualityImg->SetVisibility(ESlateVisibility::Hidden);
	CountTxt->SetVisibility(ESlateVisibility::Hidden);
}

void UBackpackSlotWidget::OnClick()
{
	if (Context != EBackpackSlotContext::EBC_None && SlotData)
	{
		if (SlotData->bIsEquipment)
		{
			auto* Window = FWindowWidgetManager::GetInstance()->OpenWindow<UEquipmentInfoWindowWidget>(EWindowWidgetID::EWWT_EquipmentInfo);
			Window->InitializeData(SlotData, Context);
		}
		else
		{
			auto* Window = FWindowWidgetManager::GetInstance()->OpenWindow<UItemInfoWindowWidget>(EWindowWidgetID::EWWT_ItemInfo);
			Window->InitializeData(SlotData, Context);
		}
	}
}
