// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterHealthBarWidget.h"

#include "Components/ProgressBar.h"

bool UMonsterHealthBarWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
		HealthBar->SetPercent(0.0f);
	}
	return Result;
}

void UMonsterHealthBarWidget::SetPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}
