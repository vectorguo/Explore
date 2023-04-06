// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Hero/MainHeroBlackboard.h"


// Sets default values
ANpc::ANpc()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	//添加Mesh
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	//添加碰撞
	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionVolume->SetupAttachment(GetRootComponent());

	//创建UI Widget
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("UIWidgetRoot"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ANpc::BeginPlay()
{
	Super::BeginPlay();

	//设置碰撞参数
	CollisionVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ANpc::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ANpc::OnOverlapEnd);

	//重新获取WidgetComponent（不确定什么原因导致在BeginPlay里WidgetComponent会变成空指针，需要重新获取）
	if (WidgetComponent == nullptr)
	{
		WidgetComponent = Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()));	
	}
}

void ANpc::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto* MainHero = Cast<AMainHero>(OtherActor))
	{
		MainHero->GetBlackboard()->SetInteractiveNpc(this);
	}
}

void ANpc::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (const auto* MainHero = Cast<AMainHero>(OtherActor))
	{
		MainHero->GetBlackboard()->SetInteractiveNpc(nullptr);
	}
}

