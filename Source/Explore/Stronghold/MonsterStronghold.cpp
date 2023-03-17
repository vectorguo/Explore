// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStronghold.h"

#include "NavigationSystem.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Explore/Characters/Hero/MainHeroBlackboard.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Monster/MonsterElite.h"
#include "Explore/Characters/Monster/MonsterNormal.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMonsterStronghold::AMonsterStronghold()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneComponent;

	//创建警戒范围
	WarningVolume = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WarningVolume"));
	WarningVolume->SetupAttachment(GetRootComponent());
	WarningVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	WarningVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	WarningVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	WarningVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AMonsterStronghold::BeginPlay()
{
	Super::BeginPlay();

	//添加警戒范围检测函数
	WarningVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WarningVolume->OnComponentBeginOverlap.AddDynamic(this, &AMonsterStronghold::OnWarningOverlapBegin);
	WarningVolume->OnComponentEndOverlap.AddDynamic(this, &AMonsterStronghold::OnWarningOverlapEnd);
	
	if (auto* World = GetWorld())
	{
		//NavigationSystem
		UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(World->GetNavigationSystem());
		
		//创建普通小怪
		if (NormalMonsterAsset && NormalMonsterLocationRoot)
		{
			TArray<AActor*> locationPoints;
			NormalMonsterLocationRoot->GetAttachedActors(locationPoints);

			for (const auto* Point : locationPoints)
			{
				auto worldLocation = Point->GetActorLocation();
				auto worldRotation = Point->GetActorRotation();
				if (auto* Monster = World->SpawnActor<AMonsterNormal>(NormalMonsterAsset, worldLocation, worldRotation))
				{
					Monster->SetStronghold(this);

					//设置NavMesh上的位置
					FNavLocation GroundPoint;
					if (NavSystem->ProjectPointToNavigation(worldLocation, GroundPoint))
					{
						Monster->SetActorLocation(GroundPoint.Location);
					}

					//记录到Array里
					Monsters.Emplace(Monster);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Create Monster Failed"));
				}
			}
		}
	
		//创建精英小怪
		if (EliteMonsterAsset && EliteMonsterLocationRoot)
		{
			TArray<AActor*> locationPoints;
			EliteMonsterLocationRoot->GetAttachedActors(locationPoints);

			for (const auto* Point : locationPoints)
			{
				auto worldLocation = Point->GetActorLocation();
				auto worldRotation = Point->GetActorRotation();
				if (auto* Monster = World->SpawnActor<AMonsterElite>(EliteMonsterAsset, worldLocation, worldRotation))
				{
					Monster->SetStronghold(this);

					//设置NavMesh上的位置
					FNavLocation GroundPoint;
					if (NavSystem->ProjectPointToNavigation(worldLocation, GroundPoint))
					{
						Monster->SetActorLocation(GroundPoint.Location);
					}

					//记录到Array里
					Monsters.Emplace(Monster);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Create Monster Failed"));
				}
			}
		}
	}
}

// Called every frame
void AMonsterStronghold::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonsterStronghold::OnWarningOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto* MainHero = Cast<AMainHero>(OtherActor))
	{
		if (auto* blackboard = MainHero->GetBlackboard())
		{
			blackboard->SetMonsterStronghold(this);
		}
	}
}

void AMonsterStronghold::OnWarningOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (auto* MainHero = Cast<AMainHero>(OtherActor))
	{
		if (auto* blackboard = MainHero->GetBlackboard())
		{
			blackboard->SetMonsterStronghold(nullptr);
		}
	}
}