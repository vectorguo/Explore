// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHero.h"

#include "MainHeroState.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/Hero/MainHeroBlackboard.h"
#include "Explore/Characters/CharacterEquipAndItem/CharacterEquipment.h"
#include "Explore/Characters/CharacterEquipAndItem/CharacterItem.h"
#include "Explore/Characters/Monster/MonsterBase.h"
#include "Explore/Table/TableEquipment.h"
#include "Explore/Table/TableLevel.h"
#include "Explore/Table/TableMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"
#include <NavigationSystem.h>

// Sets default values
AMainHero::AMainHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//创建SprintArm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 125.0f;
	CameraBoom->bUsePawnControlRotation = true;

	//创建跟随相机
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;

	PathFollowing = CreateDefaultSubobject<UPathFollowingComponent>(TEXT("PathFollowing"));
}

// Called when the game starts or when spawned
void AMainHero::BeginPlay()
{
	Super::BeginPlay();

	//设置移动参数
	auto* Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (Movement)
	{
		Movement->MaxWalkSpeed = 100.0f;
		Movement->MaxWalkSpeedCrouched = 100.0f;
	}

	//初始化碰撞
	if (auto* CapsuleCollision = GetCapsuleComponent())
	{
		CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		CapsuleCollision->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
		CapsuleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		CapsuleCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);	
	}
	
	//获取背包数据
	Backpack = GetPlayerState<AMainHeroState>();
	
	//创建Blackboard
	Blackboard = NewObject<UMainHeroBlackboard>(this, TEXT("BlackboardC"));
	
	//添加基本的攻击技能
	SkillManager->AddSkill(0);
	SkillManager->AddSkill(1);
	SkillManager->AddSkill(4);

	//设置初始武器
	const FBackpackSlotData InitialWeapon(AMainHeroState::GenerateGuid(), 1, 1, 1, true);
	WearEquipment(&InitialWeapon);

	//将英雄拉到Navmesh上
	auto* NavSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
	FNavLocation RandomReachablePoint;
	if (NavSystem->ProjectPointToNavigation(GetActorLocation(), RandomReachablePoint))
	{
		SetActorLocation(RandomReachablePoint.Location);
	}
	
	//记录主角
	if (auto* GameManager = UExploreGameManager::GetInstance())
	{
		GameManager->SetMainHero(this);	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameManager is not initialized"));
	}
}

// Called every frame
void AMainHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AMainHero::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//修改血量
	Attribute->ModifyHealth(DamageAmount);

	// //检测角色是否死亡
	// if (Attribute->GetHealth() <= 0)
	// {
	// }
	
	return DamageAmount;
}

void AMainHero::OnKillMonster(const AMonsterBase* Monster)
{
	//获取经验
	const auto MonsterExperience = Monster->GetAttribute()->GetExperience();
	auto CurrentExperience = Attribute->GetExperience() + MonsterExperience;
	Attribute->SetExperience(CurrentExperience);

	//检测是否可以升级
	auto CurrentLevel = Attribute->GetLevel();
	while (true)
	{
		const auto* CurrentLevelConfig = FTableLevel::GetRow(CurrentLevel);
		if (CurrentExperience > CurrentLevelConfig->TotalExperience)
		{
			++CurrentLevel;
			if (FTableLevel::GetRow(CurrentLevel))
			{
				Attribute->SetLevel(CurrentLevel);	
			}
			else
			{
				//已满级
				break;
			}
		}
		else
		{
			break;
		}
	}

	//获取金币
	if (auto* HeroState = GetPlayerState<AMainHeroState>())
	{
		const auto* MonsterConfig = FTableMonster::GetRow(Monster->GetMonsterID());
		HeroState->AddCoin(MonsterConfig->DropCoin);
	}
}

void AMainHero::WearEquipment(const FBackpackSlotData* EquipmentData)
{
	const auto* EquipConfig = FTableEquipment::GetRow(EquipmentData->Tid);
	if (EquipConfig == nullptr)
	{
		return;
	}
	
	const auto EquipPart = static_cast<EEquipmentPart>(EquipConfig->Part);
	if (EquipmentsMap.Contains(EquipPart))
	{
		//脱下当前部位的装备
		TakeOffEquipment(EquipPart);
	}

	//穿戴新的装备
	auto* NewEquip = NewObject<UCharacterEquipment>(this);
	NewEquip->SetEquipmentData(EquipmentData);
	NewEquip->SetEquipmentPart(EquipPart);
	NewEquip->SetHeroOwner(this);
	NewEquip->AddEquipmentEffect();
	NewEquip->CreateFacade();
	EquipmentsMap.Emplace(EquipPart, NewEquip);
	
	//将装备从背包中移除
	Backpack->RemoveEquipmentFromBackpack(EquipmentData->Guid);
}

void AMainHero::TakeOffEquipment(int32 EquipmentGuid)
{
	for (auto Iter = EquipmentsMap.CreateConstIterator(); Iter; ++Iter)
	{
		auto* Equipment = Iter->Value;
		if (Equipment->GetEquipmentGuid() == EquipmentGuid)
		{
			Equipment->RemoveEquipmentEffect();
			Equipment->DestroyFacade();

			//将脱下的装备加入背包
			if (auto* HeroState = GetPlayerState<AMainHeroState>())
			{
				HeroState->AddEquipmentToBackpack(Equipment->GetEquipmentData());
			}

			EquipmentsMap.Remove(Iter->Key);
			break;
		}
	}
}

void AMainHero::TakeOffEquipment(EEquipmentPart Part)
{
	UCharacterEquipment* Equipment;
	if (EquipmentsMap.RemoveAndCopyValue(Part, Equipment))
	{
		UE_LOG(LogTemp, Warning, TEXT("TakeOff Equip2 Part = %d, Tid = %d"), (int)Part, Equipment->GetEquipmentTid());
		Equipment->RemoveEquipmentEffect();
		Equipment->DestroyFacade();

		//将脱下的装备加入背包
		Backpack->AddEquipmentToBackpack(Equipment->GetEquipmentData());
	}
}

bool AMainHero::HasEquipment(int32 EquipmentGuid) const
{
	for (auto Iter = EquipmentsMap.CreateConstIterator(); Iter; ++Iter)
	{
		if (Iter->Value->GetEquipmentGuid() == EquipmentGuid)
		{
			return true;
		}
	}
	return false;
}

bool AMainHero::HasEquipment(EEquipmentPart Part) const
{
	return EquipmentsMap.Contains(Part);
}

void AMainHero::UseItem(const FBackpackSlotData* InItemData)
{
	if (Items.ContainsByPredicate([InItemData](const UCharacterItem* V) {return V->GetItemGuid() == InItemData->Guid;}))
	{
		return;
	}

	auto* NewItem = NewObject<UCharacterItem>(this);
	NewItem->SetItemData(InItemData);
	NewItem->SetHeroOwner(this);
	NewItem->AddItemEffect();
	Items.Emplace(NewItem);

	//从背包中移除Item
	Backpack->RemoveItemFromBackpack(InItemData->Guid);
}
