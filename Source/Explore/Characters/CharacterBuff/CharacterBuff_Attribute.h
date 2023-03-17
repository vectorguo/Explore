// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBuffBase.h"
#include "CharacterBuff_Attribute.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API UCharacterBuff_Attribute : public UCharacterBuffBase
{
	GENERATED_BODY()

public:
	/**
	 * @brief 初始化
	 * @param InGuid Buff的唯一ID
	 * @param BuffOwner
	 * @param BuffCauser
	 * @param BuffConfig 技能配置
	 */
	virtual void Initialize(int32 InGuid, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser, const FTableBuffRowData* BuffConfig) override;

	/**
	 * @brief 生效
	 */
	virtual void TakeEffect() override;
	
	/**
	 * @brief 销毁
	 * @param bNormal 是否正常结束
	 */
	virtual void Destroy(bool bNormal) override;
	
protected:
	/**
	 * @brief 属性类型
	 */
	EAttributeType AttributeType;

	/**
	 * @brief 属性变化值
	 */
	float DeltaValue;
};
