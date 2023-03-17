// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentInfoWindowWidget.h"

#include "BackpackSlotWidget.h"
#include "HeroInfoWindowWidget.h"
#include "WindowWidgetManager.h"
#include "Blueprint/WidgetTree.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/CharacterAttribute/CharacterAttribute.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Hero/MainHeroState.h"
#include "Explore/Characters/Hero/MainHeroStateStruct.h"
#include "Explore/Table/TableBuff.h"
#include "Explore/Table/TableEquipment.h"
#include "Explore/Table/TableEquipmentSynthesis.h"
#include "Explore/Utility/ExploreUtility.h"

UEquipmentInfoWindowWidget::UEquipmentInfoWindowWidget()
{
	WindowID = EWindowWidgetID::EWWT_EquipmentInfo;
	WindowType = EWindowWidgetType::EWWT_Dialog;
}

UEquipmentInfoWindowWidget::~UEquipmentInfoWindowWidget()
{
}

bool UEquipmentInfoWindowWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		EquipmentSlot = Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("EquipSlot")));
		EquipmentName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtEquipName")));
		EquipmentLevel = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtEquipLevel")));
		EquipmentDescription = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtEquipDesc")));
		EquipmentEffects = Cast<UVerticalBox>(GetWidgetFromName(TEXT("VbEquipEffects")));
		OperationBtnParent = Cast<USizeBox>(GetWidgetFromName(TEXT("SbOperation")));
		OperationBtnParent->SetVisibility(ESlateVisibility::Hidden);
		OperationNameTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtOperationName")));
		SellBtnParent = Cast<USizeBox>(GetWidgetFromName(TEXT("SbSell")));
		SellBtnParent->SetVisibility(ESlateVisibility::Hidden);
	}
	return Result;
}

void UEquipmentInfoWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEquipmentInfoWindowWidget::InitializeData(const FBackpackSlotData* Data, EBackpackSlotContext InContext)
{
	EquipmentData = Data;
	Context = InContext;

	const auto* EquipmentConfig = FTableEquipment::GetRow(EquipmentData->Tid);
	EquipmentSlot->InitializeData(*EquipmentData, EBackpackSlotContext::EBC_None);
	EquipmentName->SetText(FText::FromString(EquipmentConfig->Name));
	EquipmentName->SetColorAndOpacity(FExploreUtility::GetQualitySlateColor(EquipmentConfig->Quality));
	EquipmentLevel->SetText(FText::FromString("Lv." + FString::FromInt(EquipmentData->Level)));
	EquipmentDescription->SetText(FText::FromString(EquipmentConfig->Description));

	//装备属性
	const auto& Attributes = EquipmentConfig->Attributes;
	for (auto Index = 0; Index + 1 < Attributes.Num(); Index += 2)
	{
		auto* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		auto TextFont = Text->GetFont();
		TextFont.Size = 20;
		TextFont.TypefaceFontName = TEXT("Light");
		Text->SetFont(TextFont);
		
		FString InText = TEXT("属性：");
		const auto AttrType = static_cast<EAttributeType>(Attributes[Index]);
		const auto AttrValue = Attributes[Index + 1];
		switch (AttrType)
		{
			case EAttributeType::EAT_ExtraStrength:
				InText += TEXT("力量 +") + FString::FromInt(AttrValue);
				break;
			case EAttributeType::EAT_ExtraAgility:
				InText += TEXT("敏捷 +") + FString::FromInt(AttrValue);
				break;
			case EAttributeType::EAT_ExtraIntelligence:
				InText += TEXT("智力 +") + FString::FromInt(AttrValue);
				break;
			case EAttributeType::EAT_MaxHealth:
				InText += TEXT("最大生命值 +") + FString::FromInt(AttrValue);
				break;
			case EAttributeType::EAT_ExtraAttack:
				InText += TEXT("攻击 +") + FString::FromInt(AttrValue);
				break;
			case EAttributeType::EAT_ExtraArmor:
				InText += TEXT("护甲 +") + FString::FromInt(AttrValue);
				break;
			case EAttributeType::EAT_CritRate:
				InText += TEXT("暴击率 +") + FString::FromInt(AttrValue) + "%";
				break;
			case EAttributeType::EAT_CritMultiple:
				InText += TEXT("暴击伤害 +") + FString::FromInt(AttrValue * 100) + "%";
				break;
			case EAttributeType::EAT_DamageIncrease:
				InText += TEXT("战斗天赋 +") + FString::FromInt(AttrValue * 100);
				break;
			case EAttributeType::EAT_DamageDecrease:
				InText += TEXT("防御天赋 +") + FString::FromInt(AttrValue * 100);
				break;
			case EAttributeType::EAT_DamageBlock:
				InText += TEXT("格挡伤害 +") + FString::FromInt(AttrValue);
				break;
			case EAttributeType::EAT_BloodAbsorbing:
				InText += TEXT("攻击吸血 +") + FString::FromInt(AttrValue) + "%";
				break;
			case EAttributeType::EAT_MovementSpeed:
				InText += TEXT("移动速度 +") + FString::FromInt(AttrValue);
				break;
			case EAttributeType::EAT_SkillSpeed:
				InText += TEXT("攻击速度 +") + FString::FromInt(AttrValue) + "%";
				break;
			default:
				InText += TEXT("未知属性 类型：") + FString::FromInt(Attributes[Index]);
		}

		Text->SetText(FText::FromString(InText));
		EquipmentEffects->AddChildToVerticalBox(Text);
	}

	//装备Buff
	for (const auto BuffID : EquipmentConfig->Buffs)
	{
		const auto* BuffConfig = FTableBuff::GetRow(BuffID);
		
		auto* Text = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		auto TextFont = Text->GetFont();
		TextFont.Size = 20;
		TextFont.TypefaceFontName = TEXT("Light");
		Text->SetFont(TextFont);
		Text->SetText(FText::FromString(BuffConfig->Description));
		EquipmentEffects->AddChildToVerticalBox(Text);
	}

	//显示操作按钮
	switch (Context)
	{
		case EBackpackSlotContext::EBC_InBackpack:
			OperationBtnParent->SetVisibility(ESlateVisibility::Visible);
			OperationNameTxt->SetText(FText::FromString(TEXT("穿戴")));
			SellBtnParent->SetVisibility(ESlateVisibility::Visible);
			break;
		case EBackpackSlotContext::EBC_Worn:
			OperationBtnParent->SetVisibility(ESlateVisibility::Visible);
			OperationNameTxt->SetText(FText::FromString(TEXT("脱下")));
			SellBtnParent->SetVisibility(ESlateVisibility::Hidden);
			break;
		case EBackpackSlotContext::EBC_SynthResult:
			OperationBtnParent->SetVisibility(ESlateVisibility::Visible);
			OperationNameTxt->SetText(FText::FromString(TEXT("合成")));
			SellBtnParent->SetVisibility(ESlateVisibility::Hidden);
			break;
		default:
			OperationBtnParent->SetVisibility(ESlateVisibility::Hidden);
			SellBtnParent->SetVisibility(ESlateVisibility::Hidden);
			break;
	}
}

void UEquipmentInfoWindowWidget::OnClickOperation()
{
	switch (Context)
	{
	case EBackpackSlotContext::EBC_InBackpack:
		PutOnEquipment();
		break;
	case EBackpackSlotContext::EBC_Worn:
		TakeOffEquipment();
		break;
	case EBackpackSlotContext::EBC_SynthResult:
		SynthEquipment();
		break;
	default:
		break;
	}
}

void UEquipmentInfoWindowWidget::OnClickSell()
{
	auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
	auto* Backpack = MainHero->GetBackpack();
	Backpack->SellEquipmentFromBackpack(EquipmentData->Guid);

	//刷新英雄信息界面
	if (auto* HeroInfoWindow = FWindowWidgetManager::GetInstance()->GetWindow<UHeroInfoWindowWidget>(EWindowWidgetID::EWWT_HeroInfo))
	{
		HeroInfoWindow->Refresh();
	}

	//关闭当前界面
	Close();
}

void UEquipmentInfoWindowWidget::PutOnEquipment()
{
	//穿上装备
	auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
	MainHero->WearEquipment(EquipmentData);

	//刷新英雄信息界面
	if (auto* HeroInfoWindow = FWindowWidgetManager::GetInstance()->GetWindow<UHeroInfoWindowWidget>(EWindowWidgetID::EWWT_HeroInfo))
	{
		HeroInfoWindow->Refresh();
	}

	//关闭当前界面
	Close();
}

void UEquipmentInfoWindowWidget::TakeOffEquipment()
{
	//脱下装备
	auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
	MainHero->TakeOffEquipment(EquipmentData->Guid);

	//刷新英雄信息界面
	if (auto* HeroInfoWindow = FWindowWidgetManager::GetInstance()->GetWindow<UHeroInfoWindowWidget>(EWindowWidgetID::EWWT_HeroInfo))
	{
		HeroInfoWindow->Refresh();
	}

	//关闭当前界面
	Close();
}

void UEquipmentInfoWindowWidget::SynthEquipment()
{
	//合成装备
	if (auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero())
	{
		for (auto Iter = FTableEquipmentSynthesis::GetRows()->CreateConstIterator(); Iter; ++Iter)
		{
			if (Iter->Value->EquipmentTid == EquipmentData->Tid)
			{
				MainHero->GetBackpack()->SynthEquipmentInBackpack(Iter->Key);
			}
		}
	}

	//刷新Forger界面
	

	//关闭当前界面
	Close();
}
