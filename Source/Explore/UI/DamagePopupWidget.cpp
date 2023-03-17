// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagePopupWidget.h"

#include "Components/TextBlock.h"

bool UDamagePopupWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		DamageValueTxt = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageValueTxt")));
		DamageValueTxt->SetText(FText());
	}
	return Result;
}

void UDamagePopupWidget::SetDamageValue(int DamageValue)
{
	if (DamageValueTxt)
	{
		DamageValueTxt->SetText(FText::FromString(FString::FromInt(FMath::Abs(DamageValue))));
	}
}
