// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowWidget.h"

#include "WindowWidgetManager.h"

bool UWindowWidget::Initialize()
{
	auto Result = Super::Initialize();
	if (Result)
	{
		auto WorldType = GetWorld()->WorldType;
		Result = WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
	}
	return Result;
}

void UWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWindowWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UWindowWidget::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UWindowWidget::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UWindowWidget::Close()
{
	FWindowWidgetManager::GetInstance()->CloseWindow(WindowID);
}
