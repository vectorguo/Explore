// Fill out your copyright notice in the Description page of Project Settings.

#include "ForgerSynthesisSlotWidget.h"

#include "BackpackSlotWidget.h"
#include "Components/TextBlock.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Hero/MainHeroState.h"
#include "Explore/Characters/Hero/MainHeroStateStruct.h"
#include "Explore/Table/TableEquipment.h"
#include "Explore/Table/TableEquipmentSynthesis.h"
#include "Explore/Utility/ExploreUtility.h"

bool UForgerSynthesisSlotWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		
	}
	return Result;
}

void UForgerSynthesisSlotWidget::InitializeData(const FTableEquipmentSynthesisRowData* Config)
{
	SynthResultTid = Config->EquipmentTid;

	//名称
	auto* NameTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("TxtName")));
	NameTxt->SetText(FText::FromString(Config->Name));
	NameTxt->SetColorAndOpacity(FExploreUtility::GetQualitySlateColor(FTableEquipment::GetRow(Config->EquipmentTid)->Quality));
	
	//合成道具
	auto* SlotResult = Cast<UBackpackSlotWidget>(GetWidgetFromName(TEXT("SlotResult")));
	SlotResult->InitializeData(FBackpackSlotData(-1, Config->EquipmentTid, 1, 1, true), EBackpackSlotContext::EBC_SynthResult);

	//合成材料
	auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
	for (auto Index = 0; Index < 6; ++Index)
	{
		auto* SlotMaterial = Cast<UBackpackSlotWidget>(GetWidgetFromName(*(TEXT("SlotMaterial") + FString::FromInt(Index))));

		bool bValid;
		int32 Tid;
		bool bIsEquip;
		bool bHasMaterial = false;
		if (Index < Config->EquipMaterials.Num())
		{
			bValid = true;
			Tid = Config->EquipMaterials[Index];
			bIsEquip = true;
			bHasMaterial = MainHero->GetBackpack()->HasEquipmentInBackpack(Tid);
		}
		else if (Index < Config->EquipMaterials.Num() + Config->ItemMaterials.Num())
		{
			bValid = true;
			Tid = Config->EquipMaterials[Index - Config->EquipMaterials.Num()];
			bIsEquip = false;
		}
		else
		{
			bValid = false;
			Tid = -1;
			bIsEquip = false;
		}

		if (bValid)
		{
			SlotMaterial->InitializeData(FBackpackSlotData(-1, Tid, 1, bHasMaterial ? 1 : 0, bIsEquip), EBackpackSlotContext::EBC_SynthMaterial);
		}
		else
		{
			SlotMaterial->SetVisibility(ESlateVisibility::Hidden);
			if (Index > 0)
			{
				auto* OperatorTxt = Cast<UTextBlock>(GetWidgetFromName(*(TEXT("TxtPlus") + FString::FromInt(Index))));
				OperatorTxt->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UForgerSynthesisSlotWidget::OnClickSynth()
{
	//合成装备
	if (auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero())
	{
		for (auto Iter = FTableEquipmentSynthesis::GetRows()->CreateConstIterator(); Iter; ++Iter)
		{
			if (Iter->Value->EquipmentTid == SynthResultTid)
			{
				MainHero->GetBackpack()->SynthEquipmentInBackpack(Iter->Key);
			}
		}
	}

	//刷新Forger界面


}
