// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsCharacterDead.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UBTDecorator_IsCharacterDead : public UBTDecorator
{
	GENERATED_UCLASS_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
