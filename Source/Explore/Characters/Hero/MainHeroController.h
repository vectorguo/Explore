// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainHeroController.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API AMainHeroController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	/**
	 * @brief 技能释放结束
	 */
	void OnSkillEnd();

private:
	/**
	 * @brief 向前/向后移动
	 * @param Value 移动距离
	 */
	void MoveForward(float Value);

	/**
	 * @brief 向左/向右移动
	 * @param Value 移动距离
	 */
	void MoveRight(float Value);

	/**
	 * Add input (affecting Yaw) to the Controller's ControlRotation, if it is a local PlayerController.
	 * This value is multiplied by the PlayerController's InputYawScale value.
	 * @param Val Amount to add to Yaw. This value is multiplied by the PlayerController's InputYawScale value.
	 * @see PlayerController::InputYawScale
	 */
	void AddControllerYawInput(float Val);

	/**
	 * Add input (affecting Pitch) to the Controller's ControlRotation, if it is a local PlayerController.
	 * This value is multiplied by the PlayerController's InputPitchScale value.
	 * @param Val Amount to add to Pitch. This value is multiplied by the PlayerController's InputPitchScale value.
	 * @see PlayerController::InputPitchScale
	 */
	void AddControllerPitchInput(float Val);

	/**
	 * @brief 按键旋转
	 */
	void TurnAtRate(float Value);

	/**
	 * @brief 按键Look Up/Down
	 */
	void LookUpAtRate(float Value);

	/**
	 * @brief 冲刺
	 */
	void Sprint();
	
	/**
	 * @brief 鼠标左键按下
	 */
	void OnLeftMouseBtnDown();

	/**
	 * @brief 鼠标左键松开
	 */
	void OnLeftMouseBtnUp();

	/**
	 * @brief 鼠标右键按下
	 */
	void OnRightMouseBtnDown();

	/**
	 * @brief 鼠标右键松开
	 */
	void OnRightMouseBtnUp();

	/**
	 * @brief 打开背包界面
	 */
	void OnOpenBackpack();

	/**
	 * @brief 与NPC交互
	 */
	void OnInteract();

private:
	/**
	 * @brief 所属英雄
	 */
	UPROPERTY()
	class AMainHero* OwnerHero = nullptr;

	/**
	 * @brief 镜头旋转速率
	 */
	float BaseTurnRate = 65.0f;
	float BaseLookUpRate = 65.0f;
	
	/**
	 * @brief 是否正在按下鼠标左键
	 */
	bool bIsPressingLeftMouseBtn = false;

	/**
	 * @brief 是否正在按下鼠标右键
	 */
	bool bIsPressingRightMouseBtn = false;

	/**
	 * @brief 向前/右移动的值
	 */
	float MoveForwardValue;
	float MoveRightValue;
};
