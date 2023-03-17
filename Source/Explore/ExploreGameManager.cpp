// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreGameManager.h"

#include "Table/TableBuff.h"
#include "Table/TableDropItem.h"
#include "Table/TableEquipment.h"
#include "Table/TableEquipmentSynthesis.h"
#include "Table/TableItem.h"
#include "Table/TableLevel.h"
#include "Table/TableMonster.h"
#include "Table/TableShop.h"
#include "Table/TableSkill.h"
#include "Table/TableString.h"
#include "Table/TableTimeline.h"
#include "Timeline/ExploreTimelineManager.h"
#include "UI/WindowWidgetManager.h"

UExploreGameManager::~UExploreGameManager()
{
	MainHero = nullptr;

	//销毁配置表数据
	DestroyTables();
}

UExploreGameManager* UExploreGameManager::GetInstance()
{
	return GEngine ? Cast<UExploreGameManager>(GEngine->GameSingleton) : nullptr;
}

void UExploreGameManager::Initialize()
{
	//初始化TimelineManager
	TimelineManager = NewObject<UExploreTimelineManager>(this, TEXT("TimelineManager"));
}

void UExploreGameManager::SetMainHero(AMainHero* Hero)
{
	MainHero = Hero;

	//创建主窗口
	FWindowWidgetManager::GetInstance()->OpenWindow(EWindowWidgetID::EWWT_Main);
}

void UExploreGameManager::InitializeTables() const
{
	UE_LOG(LogTemp, Warning, TEXT("初始化配置表"));
	FTableBuff::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableBuff.TableBuff'"));
	FTableDropItem::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableDropItem.TableDropItem'"));
	FTableEquipment::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableEquipment.TableEquipment'"));
	FTableEquipmentSynthesis::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableEquipmentSynthesis.TableEquipmentSynthesis'"));
	FTableItem::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableItem.TableItem'"));
	FTableLevel::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableLevel.TableLevel'"));
	FTableMonster::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableMonster.TableMonster'"));
	FTableShop::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableShop.TableShop'"));
	FTableSkill::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableSkill.TableSkill'"));
	FTableString::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableString.TableString'"));
	FTableTimeline::Initialize(TEXT("/Script/Engine.DataTable'/Game/Tables/TableTimeline.TableTimeline'"));
}

void UExploreGameManager::DestroyTables() const
{
	UE_LOG(LogTemp, Warning, TEXT("销毁配置表"));
	FTableBuff::Destroy();
	FTableDropItem::Destroy();
	FTableEquipment::Destroy();
	FTableEquipmentSynthesis::Destroy();
	FTableItem::Destroy();
	FTableLevel::Destroy();
	FTableMonster::Destroy();
	FTableShop::Destroy();
	FTableSkill::Destroy();
	FTableString::Destroy();
	FTableTimeline::Destroy();
}


