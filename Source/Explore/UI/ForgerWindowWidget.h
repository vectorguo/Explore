// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowWidget.h"
#include "ForgerWindowWidget.generated.h"

struct FBackpackSlotData;

/**
 * 装备信息界面
 */
UCLASS()
class EXPLORE_API UForgerWindowWidget : public UWindowWidget
{
	GENERATED_BODY()

protected:
	UForgerWindowWidget();
	virtual ~UForgerWindowWidget() override;
	
public:
	/**
	 * @brief 初始化
	 * @return 初始化是否成功
	 */
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<class UForgerSynthesisSlotWidget> ForgerSynthesisSlotClass;
};
