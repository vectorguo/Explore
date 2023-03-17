// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ForgerSynthesisSlotWidget.generated.h"

/**
 * 装备信息界面
 */
UCLASS()
class EXPLORE_API UForgerSynthesisSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief 初始化
	 * @return 初始化是否成功
	 */
	virtual bool Initialize() override;

	/**
	 * @brief 初始化数据
	 * @param Config 配置
	 */
	void InitializeData(const struct FTableEquipmentSynthesisRowData* Config);

protected:
};
