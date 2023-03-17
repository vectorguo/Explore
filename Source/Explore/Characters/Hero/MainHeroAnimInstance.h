// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainHeroAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UMainHeroAnimInstance : public UAnimInstance
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
	class AMainHero* Hero;
	
	/**
	 * @brief 移动速度
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float MovementSpeed;

	/**
	 * @brief 是否滞空
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	bool bIsInAir;
};
