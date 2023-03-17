// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterStronghold.generated.h"

/**
 * 怪物据点
 */
UCLASS()
class EXPLORE_API AMonsterStronghold : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterStronghold();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnWarningOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnWarningOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief 获取预警区域
	 * @return 预警区域
	 */
	FORCEINLINE class UCapsuleComponent* GetWarningVolume() const
	{
		return WarningVolume;
	}
	
	/**
	 * @brief 获取据点下的所有小怪
	 * @return 所有小怪
	 */
	FORCEINLINE const TArray<class AMonsterBase*>& GetMonsters() const
	{
		return Monsters;
	}

protected:
	/**
	 * @brief 警戒范围
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MonsterConfig")
	class UCapsuleComponent* WarningVolume;
	
	/**
	 * @brief 普通小怪
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MonsterConfig")
	TSubclassOf<class AMonsterNormal> NormalMonsterAsset;

	/**
	 * @brief 普通小怪位置根节点
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "MonsterConfig")
	AActor* NormalMonsterLocationRoot;

	/**
	 * @brief 普通小怪
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MonsterConfig")
	TSubclassOf<class AMonsterElite> EliteMonsterAsset;

	/**
	 * @brief 精英小怪位置根节点
	 */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "MonsterConfig")
	AActor* EliteMonsterLocationRoot;

	/**
	 * @brief 该据点所有的怪物
	 */
	UPROPERTY()
	TArray<class AMonsterBase*> Monsters;
};
