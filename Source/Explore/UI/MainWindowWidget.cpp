// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWindowWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/CharacterAttribute/CharacterAttribute.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Hero/MainHeroState.h"
#include "Explore/Table/TableLevel.h"

UMainWindowWidget::UMainWindowWidget()
{
	WindowID = EWindowWidgetID::EWWT_Main;
	WindowType = EWindowWidgetType::EWWT_Main;
	bAllowGameInput = true;
}

bool UMainWindowWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
		auto* MainHeroAttribute = MainHero->GetAttribute();
		MainHeroAttribute->OnHealthChange.AddDynamic(this, &UMainWindowWidget::OnHealthChange);
		MainHeroAttribute->OnMaxHealthChange.AddDynamic(this, &UMainWindowWidget::OnMaxHealthChange);
		MainHeroAttribute->OnExperienceChange.AddDynamic(this, &UMainWindowWidget::OnExperienceChange);
		MainHeroAttribute->OnLevelChange.AddDynamic(this, &UMainWindowWidget::OnLevelChange);

		auto* Backpack = MainHero->GetBackpack();
		Backpack->OnCoinChange.AddDynamic(this, &UMainWindowWidget::OnCoinChange);

		//等级
		LevelTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelTxt")));
		LevelTxt->SetText(FText::FromString(FString("Lv.1")));
		
		//经验条
		ExperienceBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ExperienceBar")));
		ExperienceBar->SetPercent(0.0f);
		ExperienceTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("ExperienceTxt")));
		ExperienceTxt->SetText(FText::FromString(FString("0/") + FString::FromInt(FTableLevel::GetRow(1)->Experience)));

		//血量条
		HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
		HealthBar->SetPercent(MainHeroAttribute->GetHealthPercent());
		HealthTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("HealthTxt")));
		HealthTxt->SetText(FText::FromString(FString::FromInt(MainHeroAttribute->GetHealth()) + FString("/") + FString::FromInt(MainHeroAttribute->GetMaxHealth())));
		
		//魔法条
		MagicBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
		MagicBar->SetPercent(1.0f);
		MagicTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("MagicTxt")));
		MagicTxt->SetText(FText());

		//金币
		CoinValueTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoinValueTxt")));
		CoinValueTxt->SetText(FText::FromString(FString::FromInt(Backpack->GetCoin())));
	}
	return Result;
}

void UMainWindowWidget::OnHealthChange(UCharacterAttribute* Attribute, float Health, float HealthDelta)
{
	if (Attribute && HealthBar)
	{
		HealthBar->SetPercent(Attribute->GetHealthPercent());
		if (HealthTxt)
		{
			HealthTxt->SetText(FText::FromString(FString::FromInt(Attribute->GetHealth()) + FString("/") + FString::FromInt(Attribute->GetMaxHealth())));
		}
	}
}

void UMainWindowWidget::OnMaxHealthChange(UCharacterAttribute* Attribute, float Health, float HealthDelta)
{
	if (Attribute && HealthBar)
	{
		HealthBar->SetPercent(Attribute->GetHealthPercent());
		if (HealthTxt)
		{
			HealthTxt->SetText(FText::FromString(FString::FromInt(Attribute->GetHealth()) + FString("/") + FString::FromInt(Attribute->GetMaxHealth())));
		}
	}
}

void UMainWindowWidget::OnExperienceChange(UCharacterAttribute* Attribute, float Experience)
{
	if (Attribute && ExperienceBar)
	{
		auto LastLevelTotalExperience = 0;
		if (Attribute->GetLevel() > 1)
		{
			LastLevelTotalExperience = FTableLevel::GetRow(Attribute->GetLevel() - 1)->TotalExperience;
		}

		const float CurrentLevelExperience = Experience - LastLevelTotalExperience;
		const auto* CurrentLevelConfig = FTableLevel::GetRow(Attribute->GetLevel());
		ExperienceBar->SetPercent(FMath::Min(1.0f, CurrentLevelExperience / CurrentLevelConfig->Experience));

		if (ExperienceTxt)
		{
			ExperienceTxt->SetText(FText::FromString(FString::FromInt(CurrentLevelExperience) + FString("/") + FString::FromInt(CurrentLevelConfig->Experience)));
		}
	}
}

void UMainWindowWidget::OnLevelChange(UCharacterAttribute* Attribute, int32 Level)
{
	if (Attribute && LevelTxt)
	{
		const auto Content = "Lv." + FString::FromInt(Level);
		LevelTxt->SetText(FText::FromString(Content));

		//更新经验条
		OnExperienceChange(Attribute, Attribute->GetExperience());
	}
}

void UMainWindowWidget::OnCoinChange(int32 Coin)
{
	if (CoinValueTxt)
	{
		CoinValueTxt->SetText(FText::FromString(FString::FromInt(Coin)));	
	}
}
