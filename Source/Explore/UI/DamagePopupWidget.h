// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamagePopupWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UDamagePopupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	/**
	 * @brief 设置伤害数字
	 * @param DamageValue 伤害数字
	 */
	void SetDamageValue(int DamageValue);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DamageValueTxt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	float LifeTime = 2.0f;
};
