// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterAttribute/CharacterAttribute.h"
#include "CharacterBuff/CharacterBuffComponent.h"
#include "CharacterSkill/CharacterSkillComponent.h"
#include "GameFramework/Character.h"
#include "ExploreCharacter.generated.h"

UCLASS()
class EXPLORE_API AExploreCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExploreCharacter();
	virtual ~AExploreCharacter() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * @brief Apply damage to this actor.
	 * @param DamageAmount How much damage to apply
	 * @param DamageEvent Data package that fully describes the damage received.
	 * @param EventInstigator The Controller responsible for the damage.
	 * @param DamageCauser The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	 * @return The amount of damage actually applied.
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	/**
	 * @brief 播放Montage动画
	 * @param SectionName 要播放的Section名称
	 * @param PlayRate 动画播放速度
	 */
	virtual void PlayMontage(const FName& SectionName, float PlayRate = 1.0f);

	/**
	 * @brief 暂停Montage动画
	 */
	virtual void PauseMontage();

	/**
	 * @brief 停止播放Montage动画
	 * @param InBlendOutTime 融合时间
	 */
	virtual void StopMontage(float InBlendOutTime);

	/**
	 * @brief 挂载特效
	 * @param Effect 特效Actor
	 * @param SocketName 挂载的Socket名称
	 * @param bFromTimeline 是否是从Timeline上触发的
	 */
	void AttachEffect(AActor* Effect, const FName& SocketName, bool bFromTimeline);

	/**
	 * @brief 卸载特效
	 * @param Effect 特效
	 */
	void DetachEffect(AActor* Effect);
	
	/**
	 * @brief 获取Buff管理器
	 */
	FORCEINLINE class UCharacterAttribute* GetAttribute() const
	{
		return Attribute;
	}

	/**
	 * @brief 获取伤害类型
	 */
	FORCEINLINE TSubclassOf<UDamageType>& GetDamageType()
	{
		return DamageTypeClass;
	}

	FORCEINLINE const TSubclassOf<UDamageType>& GetDamageType() const
	{
		return DamageTypeClass;
	}
	
	/**
	 * @brief 获取Buff管理器
	 */
	FORCEINLINE class UCharacterBuffComponent* GetBuffManager() const
	{
		return BuffManager;
	}

	/**
	 * @brief 获取Skill管理器
	 */
	FORCEINLINE UCharacterSkillComponent* GetSkillManager() const
	{
		return SkillManager;
	}

	/**
	 * @brief 是否死亡
	 * @return 是否死亡
	 */
	FORCEINLINE bool IsDead() const
	{
		return Attribute->GetHealth() <= 0;
	}
	
	/**
	 * @brief 设置角色是否可见
	 * @param Visible 是否可见
	 * @param bIncludeTick 是否包含Tick
	 */
	void SetVisible(bool Visible, bool bIncludeTick = true);
	
	/**
	 * @brief 设置Widget是否可见
	 * @param Visible 是否可见
	 */
	void SetWidgetVisible(bool Visible);

	/**
	 * @brief 死亡
	 */
	virtual void Die();

	/**
	 * @brief 死亡结束回调
	 */
	virtual void OnDeathEnd();

	/**
	 * @brief 复活
	 */
	virtual void Revive();

protected:
	/**
	 * @brief 动画Montage
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
	class UAnimMontage* AnimMontage;

	/**
	 * @brief 属性模板
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attribute")
	TSubclassOf<UCharacterAttribute> AttributeClass;
	
	/**
	 * @brief 角色属性
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Attribute")
	UCharacterAttribute* Attribute = nullptr;

	/**
	 * @brief 伤害类型
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute")
	TSubclassOf<UDamageType> DamageTypeClass;

	/**
	 * @brief Buff管理器
	 */
	UPROPERTY()
	UCharacterBuffComponent* BuffManager = nullptr;
	
	/**
	 * @brief 技能管理器
	 */
	UPROPERTY()
	UCharacterSkillComponent* SkillManager = nullptr;

	/**
	 * @brief 特效列表
	 */
	UPROPERTY()
	TArray<AActor*> Effects;

	/**
	 * @brief UIWidget
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* WidgetComponent;
};
