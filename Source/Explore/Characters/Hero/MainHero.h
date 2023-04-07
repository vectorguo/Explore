// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/ExploreEnum.h"
#include "MainHero.generated.h"

class UCharacterEquipment;
class UCharacterItem;

UCLASS()
class EXPLORE_API AMainHero : public AExploreCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * @brief Apply damage to this actor.
	 * @param DamageAmount How much damage to apply
	 * @param DamageEvent Data package that fully describes the damage received.
	 * @param EventInstigator The Controller responsible for the damage.
	 * @param DamageCauser The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	 * @return The amount of damage actually applied.
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/**
	 * @brief 击杀怪物的回调函数
	 */
	void OnKillMonster(const class AMonsterBase* Monster);

	/**
	 * @brief 获取指定部位的装备
	 * @param Part 指定的装备部位
	 * @return 指定部位的装备
	 */
	FORCEINLINE UCharacterEquipment* GetEquipment(EEquipmentPart Part)
	{
		auto Pointer = EquipmentsMap.Find(Part);
		return Pointer ? *Pointer : nullptr;
	}
	
	/**
	 * @brief 获取身上装备的所有武器
	 * @return 所有武器
	 */
	FORCEINLINE const TMap<EEquipmentPart, UCharacterEquipment*>& GetEquipments() const
	{
		return EquipmentsMap;
	}

	/**
	 * @brief 穿上装备
	 * @param EquipmentData 装备数据
	 */
	void WearEquipment(const struct FBackpackSlotData* EquipmentData);

	/**
	 * @brief 脱下指定Guid的装备
	 * @param EquipmentGuid 装备的Guid
	 */
	void TakeOffEquipment(int32 EquipmentGuid);
	
	/**
	 * @brief 脱下指定部位的装备
	 * @param Part 装备部位
	 */
	void TakeOffEquipment(EEquipmentPart Part);

	/**
	 * @brief 指定部位是否有装备
	 * @param Part 装备部位
	 * @return 是否装备
	 */
	UFUNCTION(BlueprintCallable)
	bool HasEquipment(EEquipmentPart Part) const;

	/**
	 * @brief 装备当前的武器外观
	 */
	void ArmWeaponFacade();

	/**
	 * @brief 装备当前的武器外观结束
	 */
	void OnArmWeaponFacadeEnd(int bNormal);

	/**
	 * @brief 解除当前的武器外观
	 */
	void DisarmWeaponFacade();

	/**
	 * @brief 解除当前的武器外观结束
	 */
	void OnDisarmWeaponFacade(int bNormal);

	/**
	 * @brief 是否装备了武器外观
	 */
	UFUNCTION(BlueprintCallable)
	bool HasArmedWeaponFacade() const
	{
		return bHasArmedFacade;
	}

	UFUNCTION(BlueprintCallable)
	bool IsArmingOrDisarmingWeaponFacade() const
	{
		return bArmingOrDisarmingFacade;
	}

	/**
	 * @brief 使用道具
	 * @param InItemData Item数据
	 */
	void UseItem(const FBackpackSlotData* InItemData);

	/**
	 * @brief 获取背包
	 * @return 背包
	 */
	FORCEINLINE class AMainHeroState* GetBackpack() const
	{
		return Backpack;
	}
	
	/**
	 * @brief 获取CameraBoom
	 */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const
	{
		return CameraBoom;
	}

	/**
	 * @brief 增加相机与角色之间的距离
	 */
	void AddCameraArmLength(float DeltaLength);
	
	/**
	 * @brief 获取跟随相机
	 */
	FORCEINLINE class UCameraComponent* GetFollowCamera() const
	{
		return FollowCamera;
	}

	/**
	 * @brief 获取Blackboard
	 * @return Blackboard
	 */
	FORCEINLINE class UMainHeroBlackboard* GetBlackboard() const
	{
		return Blackboard;
	}

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	class UPathFollowingComponent* PathFollowing;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Blackboard")
	class UMainHeroBlackboard* Blackboard = nullptr;

private:
	/**
	 * @brief 英雄身上装备的所有武器
	 */
	UPROPERTY()
	TMap<EEquipmentPart, UCharacterEquipment*> EquipmentsMap;

	/**
	 * @brief 是否装备的外观
	 */
	bool bHasArmedFacade = false;
	bool bArmingOrDisarmingFacade = false;

	/**
	 * @brief 英雄身上携带的所有道具
	 */
	UPROPERTY()
	TArray<UCharacterItem*> Items;

	/**
	 * @brief 背包
	 */
	UPROPERTY()
	class AMainHeroState* Backpack; 
};