// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Explore/Characters/ExploreCharacter.h"
#include "MonsterBase.generated.h"

UCLASS()
class EXPLORE_API AMonsterBase : public AExploreCharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
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
	 * @brief 死亡
	 */
	virtual void Die() override;

	/**
	 * @brief 死亡结束回调
	 */
	virtual void OnDeathEnd() override;
	
	/**
	 * @brief 复活
	 */
	virtual void Revive() override;

	/**
	 * @brief 创建掉落物
	 */
	void CreateDropItems() const;

	/**
	 * @brief 获取ID
	 * @return ID
	 */
	FORCEINLINE int32 GetMonsterID() const
	{
		return MonsterID;
	}

	/**
	 * @brief 获取怪物所在的据点
	 * @return 怪物所在的据点
	 */
	FORCEINLINE class AMonsterStronghold* GetStronghold() const
	{
		return Stronghold;
	}

	/**
	 * @brief 设置怪物所在据点
	 * @param NewStronghold 怪物所在据点
	 */
	FORCEINLINE void SetStronghold(class AMonsterStronghold* NewStronghold)
	{
		Stronghold = NewStronghold;
	}
	
protected:
	/**
	 * @brief 怪物ID
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Monster")
	int32 MonsterID;

	/**
	 * @brief UI血条模板
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Monster | UI")
	TSubclassOf<UUserWidget> HealthBarClass;

	/**
	 * @brief 血条
	 */
	UPROPERTY()
	class UMonsterHealthBarWidget* HealthBarWidget;

	/**
	 * @brief 所在的据点
	 */
	UPROPERTY()
	AMonsterStronghold* Stronghold;
};
