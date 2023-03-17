// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBuffComponent.generated.h"

class AExploreCharacter;
class UCharacterBuffBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EXPLORE_API UCharacterBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCharacterBuffComponent();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief 添加Buff
	 * @param BuffTid BuffTID
	 * @param Causer 施加Buff的角色
	 * @return Buff的GUID
	 */
	int32 AddBuff(int32 BuffTid, AExploreCharacter* Causer);

	/**
	 * @brief 删除Buff
	 * @param BuffGuid Buff的唯一ID
	 */
	void RemoveBuff(int32 BuffGuid);

	/**
	 * @brief 调用攻击前触发的buff
	 * @param Target 目标
	 */
	void InvokeBuffBeforeAtk(AExploreCharacter* Target);

	/**
	 * @brief 调用攻击后触发的buff
	 * @param Target 目标
	 */
	void InvokeBuffAfterAtk(AExploreCharacter* Target);

private:
	/**
	 * @brief 创建Buff
	 * @param BuffTid BuffTID
	 * @param Causer 施加Buff的角色
	 * @return 创建的Buff
	 */
	UCharacterBuffBase* CreateBuff(int32 BuffTid, AExploreCharacter* Causer);

	/**
	 * @brief 根据所有指定Buff组的Buff
	 * @param BuffGroup Buff组
	 */
	void RemoveBuffsByGroup(int32 BuffGroup);

private:
	/**
	 * @brief Buff拥有者
	 */
	UPROPERTY()
	AExploreCharacter* Owner = nullptr;

	/**
	 * @brief 所有Buff
	 */
	UPROPERTY()
	TArray<UCharacterBuffBase*> Buffs;
};
