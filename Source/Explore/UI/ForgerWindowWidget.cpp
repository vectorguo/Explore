// Fill out your copyright notice in the Description page of Project Settings.


#include "ForgerWindowWidget.h"

#include "ForgerSynthesisSlotWidget.h"
#include "WindowWidgetManager.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Explore/Table/TableEquipmentSynthesis.h"

UForgerWindowWidget::UForgerWindowWidget()
{
	WindowID = EWindowWidgetID::EWWT_Forger;
	WindowType = EWindowWidgetType::EWWT_Generic;
}

UForgerWindowWidget::~UForgerWindowWidget()
{
}

bool UForgerWindowWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		
	}
	return Result;
}

void UForgerWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	auto* SlotRoot = Cast<UVerticalBox>(GetWidgetFromName(TEXT("VbSlots")));
	if (SlotRoot && ForgerSynthesisSlotClass)
	{
		auto* WindowOwner = FWindowWidgetManager::GetInstance()->GetWindowOwner();

		auto bIsFirst = true;
		const auto* Configs = FTableEquipmentSynthesis::GetRows();
		for (auto Iter = Configs->CreateConstIterator(); Iter; ++Iter)
		{
			auto* SlotWidget = CreateWidget<UForgerSynthesisSlotWidget>(WindowOwner, ForgerSynthesisSlotClass);
			SlotWidget->InitializeData(Iter->Value);
			auto* VbSlot = SlotRoot->AddChildToVerticalBox(SlotWidget);
			VbSlot->SetHorizontalAlignment(HAlign_Left);
			VbSlot->SetVerticalAlignment(VAlign_Fill);
			if (bIsFirst)
			{
				bIsFirst = false;
				VbSlot->SetPadding(FMargin(0, 20.0f, 0, 0));
			}
		}
	}
}
