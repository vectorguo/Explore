// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WindowEnum.h"
#include "Blueprint/UserWidget.h"
#include "WindowWidget.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief 初始化
	 * @return 初始化是否成功
	 */
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	/**
	 * @brief 显示Window
	 */
	virtual void Show();

	/**
	 * @brief 隐藏Window
	 */
	virtual void Hide();
	
	/**
	 * @brief 关闭按钮点击事件
	 */
	UFUNCTION(BlueprintCallable)
	void Close();

	/**
	 * @brief 获取窗口ID
	 * @return 窗口ID
	 */
	FORCEINLINE EWindowWidgetID GetWindowID() const
	{
		return WindowID;
	}

	/**
	 * @brief 获取窗口类型
	 * @return 窗口类型
	 */
	FORCEINLINE EWindowWidgetType GetWindowType() const
	{
		return WindowType;
	}

	/**
	 * @brief 是否允许游戏输入
	 * @return 是否允许游戏输入
	 */
	FORCEINLINE bool AllowGameInput() const
	{
		return bAllowGameInput;
	}
	
protected:
	UPROPERTY()
	EWindowWidgetID WindowID = EWindowWidgetID::EWWT_None;
	
	/**
	 * @brief 窗口类型
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute")
	EWindowWidgetType WindowType = EWindowWidgetType::EWWT_Generic;

	/**
	 * @brief 是否屏蔽Game输入
	 */
	bool bAllowGameInput = false;
};
