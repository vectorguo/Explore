// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"

#include "Explore/Characters/Hero/MainHero.h"
#include "Explore/Characters/Hero/MainHeroState.h"


// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemPickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor)
	{
		if (auto* MainHero = Cast<AMainHero>(OtherActor))
		{
			if (EquipmentID > 0)
			{
				MainHero->GetBackpack()->AddEquipmentToBackpack(EquipmentID);	
			}
			else if (ItemID > 0)
			{
				MainHero->GetBackpack()->AddItemToBackpack(ItemID);
			}
			Destroy();
		}
	}
}

void AItemPickup::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}