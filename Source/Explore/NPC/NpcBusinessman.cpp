// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcBusinessman.h"

#include "Explore/UI/ShopWindowWidget.h"
#include "Explore/UI/WindowWidgetManager.h"

void ANpcBusinessman::Interact()
{
	Super::Interact();

	//打开铸造界面
	auto ShopWindow = FWindowWidgetManager::GetInstance()->OpenWindow<UShopWindowWidget>(EWindowWidgetID::EWWT_Shop);
	ShopWindow->InitializeData(ShopTid);
}

void ANpcBusinessman::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ANpcBusinessman::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
