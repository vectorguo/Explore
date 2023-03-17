// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterEquipmentFacade.h"
#include "Components/BoxComponent.h"
#include "Explore/Characters/Monster/MonsterBase.h"

// Sets default values
ACharacterEquipmentFacade::ACharacterEquipmentFacade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//创建根节点
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}