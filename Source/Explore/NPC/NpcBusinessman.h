// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Npc.h"
#include "NpcBusinessman.generated.h"

/**
 * 锻造师NPC
 */
UCLASS()
class EXPLORE_API ANpcBusinessman : public ANpc
{
	GENERATED_BODY()

public:
	/**
	 * @brief 与玩家交互
	 */
	virtual void Interact() override;
	
protected:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

protected:
	/**
	 * @brief 商店ID
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Npc | Businessman")
	int32 ShopTid;
};
