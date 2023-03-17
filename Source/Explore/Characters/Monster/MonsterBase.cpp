// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"

#include "Components/WidgetComponent.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Items/Pickups/ItemPickup.h"
#include "Explore/Table/TableDropItem.h"
#include "Explore/Table/TableEquipment.h"
#include "Explore/Table/TableMonster.h"
#include "Explore/Timeline/ExploreTimelineManager.h"
#include "Explore/UI/MonsterHealthBarWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMonsterBase::AMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();

	//处理怪物参数
	if (const auto* MonsterConfig = FTableMonster::GetRow(MonsterID))
	{
		auto* Movement = GetCharacterMovement();
		Movement->MaxWalkSpeed = MonsterConfig->MoveSpeed;
		Movement->RotationRate = FRotator(0, 720.0f, 0);

		//添加技能
		for (auto SkillID : MonsterConfig->Skills)
		{
			SkillManager->AddSkill(SkillID);	
		}

		//创建血条
		if (HealthBarClass)
		{
			if (WidgetComponent)
			{
				WidgetComponent->SetRelativeLocation(FVector(0, 0, MonsterConfig->Height));
				WidgetComponent->SetWidgetClass(HealthBarClass);
				WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
				WidgetComponent->SetDrawSize(FVector2D(120.0f, 15.0f));

				HealthBarWidget = Cast<UMonsterHealthBarWidget>(WidgetComponent->GetWidget());
				HealthBarWidget->SetPercent(Attribute->GetHealthPercent());
			}
		}
		SetWidgetVisible(false);
	}
}

float AMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//修改血量
	Attribute->ModifyHealth(DamageAmount);

	//更新血条进度
	if (HealthBarWidget)
	{
		HealthBarWidget->SetPercent(Attribute->GetHealthPercent());
	}

	//检测角色是否死亡
	if (Attribute->GetHealth() <= 0)
	{
		//调用角色击杀怪物的回调函数
		if (auto* MainHero = Cast<AMainHero>(DamageCauser))
		{
			MainHero->OnKillMonster(this);
		}
	}
	
	return DamageAmount;
}

void AMonsterBase::Die()
{
	Super::Die();
	
	//播放死亡表现
	auto* TimelineManager = UExploreGameManager::GetInstance()->GetTimelineManager();
	TimelineManager->PlayTimeline(FTableMonster::GetRow(MonsterID)->Death, 1, this);

	//创建掉落物
	CreateDropItems();
}

void AMonsterBase::OnDeathEnd()
{
	Super::OnDeathEnd();

	//隐藏怪物
	SetVisible(false, true);
}

void AMonsterBase::Revive()
{
	Super::Revive();

	//更新血条进度
	if (HealthBarWidget)
	{
		HealthBarWidget->SetPercent(Attribute->GetHealthPercent());
	}
}

void AMonsterBase::CreateDropItems() const
{
	const auto* MonsterConfig = FTableMonster::GetRow(MonsterID);
	if (const auto* DropItemConfig = FTableDropItem::GetRow(MonsterConfig->DropItem))
	{
		TArray<int32> DropResult;
		TArray<int32> Result;
		for (auto Index = 0; Index < DropItemConfig->DropEquipments.Num();)
		{
			if (DropItemConfig->DropEquipments[Index] == -1)
			{
				//下一段
				auto ResultCount = Result.Num();
				if (ResultCount > 0)
				{
					DropResult.Add(Result[FMath::RandRange(0, ResultCount - 1)]);
				}
				Result.Empty();
				++Index;
			}
			else
			{
				auto EquipTid = DropItemConfig->DropEquipments[Index];
				auto Probability = DropItemConfig->DropEquipments[Index + 1];
				if (FMath::RandRange(0, 100) <= Probability)
				{
					Result.Add(EquipTid);
				}
				Index += 2;
			}
		}

		for (const auto EquipTid : DropResult)
		{
			const TCHAR* DropItemPath = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Items/BP_Item_Equip_Green.BP_Item_Equip_Green'");
			/*switch (FTableEquipment::GetRow(EquipTid)->Quality)
			{
				default:
					DropItemPath = TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Items/BP_Item_Equip_Green.BP_Item_Equip_Green'");
			}*/

			if (auto* DropItemObj = StaticLoadObject(UBlueprint::StaticClass(), nullptr, DropItemPath); DropItemObj != nullptr)
			{
				if (auto* ItemPick = GetWorld()->SpawnActor<AItemPickup>(Cast<UBlueprint>(DropItemObj)->GeneratedClass, GetActorLocation(), FRotator::ZeroRotator))
				{
					ItemPick->SetEquipmentID(EquipTid);
				}
			}
		}
	}
}
