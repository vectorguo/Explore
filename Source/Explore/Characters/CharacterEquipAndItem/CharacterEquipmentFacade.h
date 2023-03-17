// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterEquipmentFacade.generated.h"

UCLASS()
class EXPLORE_API ACharacterEquipmentFacade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACharacterEquipmentFacade();

	/**
	 * @brief 设置所属英雄
	 * @param Hero 英雄
	 */
	FORCEINLINE void SetHeroOwner(class AExploreCharacter* Hero)
	{
		HeroOwner = Hero;
	}

protected:
	/**
	 * @brief 持有武器的角色
	 */
	UPROPERTY()
	AExploreCharacter* HeroOwner = nullptr;
};
