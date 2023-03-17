// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PlayMontage.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UBTTask_PlayMontage : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/**
	 * @brief Montage名称
	 */
	UPROPERTY(EditAnywhere, Category="Montage")
	FString MontageName;

	/**
	 * @brief Montage播放速度
	 */
	UPROPERTY(EditAnywhere, Category="Montage")
	float PlayRate;
};
