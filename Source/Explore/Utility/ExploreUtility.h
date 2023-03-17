#pragma once
#include "Explore/ExploreEnum.h"

class AExploreCharacter;
class AMainHero;
class AMonsterBase;
class AMonsterStronghold;

class FExploreUtility
{
public:
	/**
	 * @brief 查找目标点周围一定范围内的指定数量的目标
	 * @param Origin 原点
	 * @param Range 查找范围
	 * @param Count 查找数量
	 * @return 目标
	 */
	static TArray<AMonsterBase*> FindRandomMonster(const FVector& Origin, float Range, int32 Count);
	
	/**
	 * @brief 查找怪物据点里面距离基准角色一定范围内最近的目标
	 * @param Source 基准角色
	 * @param Stronghold 怪物据点
	 * @param Range 查找范围
	 * @return 距离基准角色最近的怪物
	 */
	static AMonsterBase* FindNearestMonsterInStronghold(const AExploreCharacter* Source, const AMonsterStronghold* Stronghold, float Range);

	/**
	 * @brief 计算技能的普通伤害
	 * @param CauserAttribute 技能释放者属性
	 * @param TargetAttribute 技能目标属性
	 * @return 伤害值
	 */
	static float CalculateNormalDamage(const class UCharacterAttribute* CauserAttribute, const class UCharacterAttribute* TargetAttribute);

	/**
	 * @brief 计算技能的普通伤害
	 * @param CauserAttribute 技能释放者属性
	 * @param StrengthRatio 力量系数
	 * @param AgilityRatio 敏捷系数
	 * @param IntelligenceRatio 智力系数
	 * @param ElementType 元素属性
	 * @return 伤害值
	 */
	static float CalculateAttributeDamage(const class UCharacterAttribute* CauserAttribute, float StrengthRatio, float AgilityRatio, float IntelligenceRatio, ECharacterElement ElementType);

	/**
	 * @brief 计算技能的最终伤害
	 * @param DamageValue 伤害加成和减免之前的伤害
	 * @param CauserAttribute 技能释放者属性
	 * @param TargetAttribute 技能目标属性
	 * @return 最终伤害
	 */
	static float CalculateFinalDamage(float DamageValue, const class UCharacterAttribute* CauserAttribute, const class UCharacterAttribute* TargetAttribute);
	
	/**
	 * @brief 查找某个点周围一定范围内可到达的Navmesh上的位置
	 * @param Character 要查找位置的角色
	 * @param Origin 原点
	 * @param Radius 半径
	 * @param Location 找到的位置
	 * @return 是否找到
	 */
	static bool GetRandomReachablePointInRadius(const AExploreCharacter* Character, const FVector& Origin, float Radius, FVector& Location);

	/**
	 * @brief 获取品质对应的颜色
	 * @param Quality 品质
	 * @return 品质对应的颜色
	 */
	static FColor GetQualityColor(int Quality);
	static FColor GetQualityColor(EQuality Quality);
	static FSlateColor GetQualitySlateColor(int Quality);
	static FSlateColor GetQualitySlateColor(EQuality Quality);
};
