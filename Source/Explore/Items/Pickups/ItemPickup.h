// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Explore/Items/Item.h"
#include "ItemPickup.generated.h"

UCLASS()
class EXPLORE_API AItemPickup : public AItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief 获取装备ID
	 * @return 装备ID
	 */
	FORCEINLINE int32 GetEquipmentID() const
	{
		return EquipmentID;
	}
	
	/**
	 * @brief 设置装备ID
	 * @param ID 装备ID
	 */
	FORCEINLINE void SetEquipmentID(int32 ID)
	{
		EquipmentID = ID;
	}

	/**
	 * @brief 获取道具ID
	 * @return 道具ID
	 */
	FORCEINLINE int32 GetItemID() const
	{
		return ItemID;
	}
	
	/**
	 * @brief 设置道具ID
	 * @param ID 道具ID
	 */
	FORCEINLINE void SetItemID(int32 ID)
	{
		ItemID = ID;
	}
protected:
	/**
	 * @brief 装备ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 EquipmentID = -1;

	/**
	 * @brief 道具ID
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ItemID = -1;
};
