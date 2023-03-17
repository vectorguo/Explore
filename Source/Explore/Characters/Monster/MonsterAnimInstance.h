// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 怪物AnimInstance
 */
UCLASS()
class EXPLORE_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	/**
	 * @brief 更新动画数据
	 */
	UFUNCTION(BlueprintCallable, Category="ExploreAnimation")
	void UpdateAnimationProperties();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	class AMonsterBase* Monster;
	
	/**
	 * @brief 移动速度
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MovementSpeed;
};
