// Copyright Epic Games, Inc. All Rights Reserved.


#include "ExploreGameModeBase.h"

#include "ExploreGameManager.h"
#include "Timeline/ExploreTimelineManager.h"
#include "UI/WindowWidgetManager.h"

AExploreGameModeBase::AExploreGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//GameManager初始化配置表
	UExploreGameManager::GetInstance()->InitializeTables();
}

void AExploreGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//GameManager初始化
	UExploreGameManager::GetInstance()->Initialize();
	
	//初始化WindowManager
	FWindowWidgetManager::GetInstance()->Initialize(GetWorld());
}

void AExploreGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//更新Timeline
	auto* TimelineManager = UExploreGameManager::GetInstance()->GetTimelineManager();
	TimelineManager->Tick(DeltaSeconds);
}
