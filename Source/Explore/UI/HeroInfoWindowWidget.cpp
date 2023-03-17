// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroInfoWindowWidget.h"

#include "BackpackSlotWidget.h"
#include "WindowWidgetManager.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Explore/ExploreEnum.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/CharacterEquipAndItem/CharacterEquipment.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Hero/MainHeroState.h"

UHeroInfoWindowWidget::UHeroInfoWindowWidget()
{
	WindowID = EWindowWidgetID::EWWT_HeroInfo;
	WindowType = EWindowWidgetType::EWWT_Generic;
}

UHeroInfoWindowWidget::~UHeroInfoWindowWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy UBackpackWindowWidget"));
}

bool UHeroInfoWindowWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		//英雄身上的装备槽
		HeroEquipmentSlots.Emplace(Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("EquipSlot0"))));
		HeroEquipmentSlots.Emplace(Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("EquipSlot1"))));
		HeroEquipmentSlots.Emplace(Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("EquipSlot2"))));
		HeroEquipmentSlots.Emplace(Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("EquipSlot3"))));
		HeroEquipmentSlots.Emplace(Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("EquipSlot4"))));
		HeroEquipmentSlots.Emplace(Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("EquipSlot5"))));

		//背包
		BackpackEquipmentGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("GridEquips")));
		BackpackEquipmentSb = Cast<UScrollBox>(GetWidgetFromName(TEXT("SbEquips")));
		BackpackEquipmentSb->SetVisibility(ESlateVisibility::Visible);
		BackpackItemGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("GridItems")));
		BackpackItemSb = Cast<UScrollBox>(GetWidgetFromName(TEXT("SbItems")));
		BackpackItemSb->SetVisibility(ESlateVisibility::Hidden);
	}
	return Result;
}

void UHeroInfoWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeHero();
	InitializeBackpack();
}

void UHeroInfoWindowWidget::Refresh()
{
	for (auto* EquipSlot : HeroEquipmentSlots)
	{
		EquipSlot->ClearData();
	}
	
	for (auto Index = BackpackEquipmentGrid->GetChildrenCount() - 1; Index >= 0; --Index)
	{
		BackpackEquipmentGrid->RemoveChildAt(Index);
	}

	for (auto Index = BackpackItemGrid->GetChildrenCount() - 1; Index >= 0; --Index)
	{
		BackpackItemGrid->RemoveChildAt(Index);
	}
	
	InitializeHero();
	InitializeBackpack();
}

void UHeroInfoWindowWidget::OnClickEquipTab()
{
	BackpackEquipmentSb->SetVisibility(ESlateVisibility::Visible);
	BackpackItemSb->SetVisibility(ESlateVisibility::Hidden);
}

void UHeroInfoWindowWidget::OnClickItemTab()
{
	BackpackEquipmentSb->SetVisibility(ESlateVisibility::Hidden);
	BackpackItemSb->SetVisibility(ESlateVisibility::Visible);
}

void UHeroInfoWindowWidget::InitializeHero()
{
	if (auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero())
	{
		//初始化英雄信息面板
		const auto* HeroAttribute = MainHero->GetAttribute();

		//等级
		auto* TxtLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtLevel")));
		TxtLevel->SetText(FText::FromString("Lv." + FString::FromInt(HeroAttribute->GetLevel())));
		
		//属性
		auto* TxtValue1 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue1")));
		auto* TxtValue2 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue2")));
		auto* TxtValue3 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue3")));
		auto* TxtValue4 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue4")));
		auto* TxtValue5 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue5")));
		auto* TxtValue6 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue6")));
		auto* TxtValue7 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue7")));
		auto* TxtValue8 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue8")));
		auto* TxtValue9 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue9")));
		auto* TxtValue10 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue10")));
		auto* TxtValue11 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue11")));
		auto* TxtValue12 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue12")));
		auto* TxtValue13 = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtValue13")));
		TxtValue1->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetStrength()))); 
		TxtValue2->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAgility()))); 
		TxtValue3->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetIntelligence()))); 
		TxtValue4->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetMaxHealth()))); 
		TxtValue5->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAttackValue()))); 
		TxtValue6->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAttributeValue(EAttributeType::EAT_SkillSpeed)) + "%"));
		TxtValue7->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAttributeValue(EAttributeType::EAT_BloodAbsorbing)))); 
		TxtValue8->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAttributeValue(EAttributeType::EAT_CritRate)) + "%")); 
		TxtValue9->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAttributeValue(EAttributeType::EAT_CritMultiple) * 100) + "%")); 
		TxtValue10->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetArmorValue()))); 
		TxtValue11->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAttributeValue(EAttributeType::EAT_DamageBlock)))); 
		TxtValue12->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAttributeValue(EAttributeType::EAT_DamageIncrease) * 100))); 
		TxtValue13->SetText(FText::FromString(FString::FromInt(HeroAttribute->GetAttributeValue(EAttributeType::EAT_DamageDecrease) * 100)));

		//初始化装备槽
		for (auto Index = 0; Index < HeroEquipmentSlots.Num(); ++Index)
		{
			if (const auto* EquipmentWeapon = MainHero->GetEquipment(static_cast<EEquipmentPart>(Index + 1)))
			{
				HeroEquipmentSlots[Index]->InitializeData(EquipmentWeapon->GetEquipmentData(), EBackpackSlotContext::EBC_Worn);
			}
		}
	}
}

void UHeroInfoWindowWidget::InitializeBackpack()
{
	auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
	if (MainHero && BackpackSlotClass)
	{
		auto* WindowOwner = FWindowWidgetManager::GetInstance()->GetWindowOwner();
			
		const auto* MainHeroState = MainHero->GetPlayerState<AMainHeroState>();
		const auto& EquipmentDatas = MainHeroState->GetEquipmentDatas();
		for (auto Index = 0; Index < EquipmentDatas.Num(); ++Index)
		{
			const auto& Data = EquipmentDatas[Index];
			auto* SlotWidget = CreateWidget<UBackpackSlotWidget>(WindowOwner, BackpackSlotClass);
			SlotWidget->InitializeData(Data, EBackpackSlotContext::EBC_InBackpack);
			BackpackEquipmentGrid->AddChildToUniformGrid(SlotWidget, Index / 5, Index % 5);
		}

		const auto& ItemDatas = MainHeroState->GetItemDatas();
		for (auto Index = 0; Index < ItemDatas.Num(); ++Index)
		{
			const auto& Data = ItemDatas[Index];
			auto* SlotWidget = CreateWidget<UBackpackSlotWidget>(WindowOwner, BackpackSlotClass);
			SlotWidget->InitializeData(Data, EBackpackSlotContext::EBC_InBackpack);
			BackpackItemGrid->AddChildToUniformGrid(SlotWidget, Index / 5, Index % 5);
		}
	}
}
