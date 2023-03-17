// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UMonsterHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	/**
	 * @brief 设置血量百分比
	 * @param Percent 血量百分比
	 */
	void SetPercent(float Percent);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBar;
};
