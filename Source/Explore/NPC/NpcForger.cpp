// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcForger.h"

#include "Explore/UI/WindowWidgetManager.h"

void ANpcForger::Interact()
{
	Super::Interact();

	//打开铸造界面
	FWindowWidgetManager::GetInstance()->OpenWindow(EWindowWidgetID::EWWT_Forger);
}

void ANpcForger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void ANpcForger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
