#include "ExploreUtility.h"

#include "NavigationSystem.h"
#include "NetworkMessage.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/CharacterAttribute/CharacterAttribute.h"
#include "Explore/Characters/Hero/MainHeroBlackboard.h"
#include "Explore/Characters/Monster/MonsterBase.h"
#include "Explore/Stronghold/MonsterStronghold.h"

TArray<AMonsterBase*> FExploreUtility::FindRandomMonster(const FVector& Origin, float Range, int32 Count)
{
	TArray<AMonsterBase*> Targets;

	if (const auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero())
	{
		if (const auto* Stronghold = MainHero->GetBlackboard()->GetMonsterStronghold())
		{
			const float SquaredDistance = Range * Range;
			for (auto Iter = Stronghold->GetMonsters().CreateConstIterator(); Iter; ++Iter)
			{
				auto* Monster = *Iter;
				if (Monster->IsDead())
				{
					//如果怪物已经死亡，继续检测下一个目标
					continue;
				}
				
				if (FVector::DistSquaredXY(Monster->GetActorLocation(), Origin) < SquaredDistance)
				{
					Targets.Emplace(Monster);
				}
			}
		}
	}

	if (Count >= 0)
	{
		while (Targets.Num() > Count)
		{
			Targets.RemoveAtSwap(FMath::RandRange(0, Targets.Num() - 1));
		}	
	}

	return Targets;
}

AMonsterBase* FExploreUtility::FindNearestMonsterInStronghold(const AExploreCharacter* Source, const AMonsterStronghold* Stronghold, float Range)
{
	if (!Source || !Stronghold)
	{
		return nullptr;
	}

	AMonsterBase* Target = nullptr;
			
	float MinSquaredDistance = Range * Range;
	const auto& Monsters = Stronghold->GetMonsters();
	for (auto Iter = Monsters.CreateConstIterator(); Iter; ++Iter)
	{
		auto* Monster = *Iter;
		if (Monster->IsDead())
		{
			//如果怪物已经死亡，继续检测下一个目标
			continue;
		}
				
		auto SquaredDistance = FVector::DistSquaredXY(Monster->GetActorLocation(), Source->GetActorLocation());
		if (SquaredDistance < MinSquaredDistance)
		{
			MinSquaredDistance = SquaredDistance;
			Target = *Iter;
		}
	}

	return Target;
}

float FExploreUtility::CalculateNormalDamage(const UCharacterAttribute* CauserAttribute, const UCharacterAttribute* TargetAttribute)
{
	//伤害=（攻击×参数1+参数2）/（攻击+防御×参数3+参数4）
	float DamageValue = CauserAttribute->GetAttackValue() * CauserAttribute->GetAttackValue() / (CauserAttribute->GetAttackValue() + TargetAttribute->GetArmorValue());

	//暴击检测
	auto bCritical = false;
	if (FMath::RandRange(0, 100) <= CauserAttribute->GetAttributeValue(EAttributeType::EAT_CritRate))
	{
		DamageValue *= CauserAttribute->GetAttributeValue(EAttributeType::EAT_CritMultiple);
		bCritical = true;
	}

	//闪避检测(暴击的时候无法闪避)
	if (!bCritical)
	{
		
	}
	return DamageValue;
}

float FExploreUtility::CalculateAttributeDamage(const UCharacterAttribute* CauserAttribute, float StrengthRatio, float AgilityRatio, float IntelligenceRatio, ECharacterElement ElementType)
{
	auto DamageValue = StrengthRatio * CauserAttribute->GetStrength();
	DamageValue += AgilityRatio * CauserAttribute->GetAgility();
	DamageValue += IntelligenceRatio * CauserAttribute->GetIntelligence();
	if (ElementType != ECharacterElement::ECE_None)
	{
		DamageValue *= CauserAttribute->GetElementValue(ElementType);
	}
	return DamageValue;
}

float FExploreUtility::CalculateFinalDamage(float DamageValue, const UCharacterAttribute* CauserAttribute, const UCharacterAttribute* TargetAttribute)
{
	DamageValue *= 1 + CauserAttribute->GetAttributeValue(EAttributeType::EAT_DamageIncrease);
	DamageValue -= TargetAttribute->GetAttributeValue(EAttributeType::EAT_DamageBlock);
	DamageValue *= 1 - FMath::Min(1.0f, TargetAttribute->GetAttributeValue(EAttributeType::EAT_DamageDecrease)) * (0.5 + TargetAttribute->GetLevel() / 210.0f);
	return DamageValue;
}

bool FExploreUtility::GetRandomReachablePointInRadius(const AExploreCharacter* Character, const FVector& Origin, float Radius, FVector& Location)
{
	if (auto* World = Character->GetWorld())
	{
		if (auto* NavSystem = Cast<UNavigationSystemV1>(World->GetNavigationSystem()))
		{
			FNavLocation RandomReachablePoint;
			if (NavSystem->GetRandomPointInNavigableRadius(Origin, Radius, RandomReachablePoint))
			{
				Location = RandomReachablePoint.Location;
				return true;
			}	
		}
	}
	return false;
}

FColor FExploreUtility::GetQualityColor(int Quality)
{
	return GetQualityColor(static_cast<EQuality>(Quality));
}

FColor FExploreUtility::GetQualityColor(EQuality Quality)
{
	switch (Quality)
	{
	case EQuality::EQ_White:
		return FColor::White;
	case EQuality::EQ_Grey:
		return FColor(226, 255, 113, 255);
	case EQuality::EQ_Green:
		return FColor::Green;
	case EQuality::EQ_Blue:
		return FColor::Blue;
	case EQuality::EQ_Purple:
		return FColor::Purple;
	case EQuality::EQ_Yellow:
		return FColor::Yellow;
	case EQuality::EQ_Orange:
		return FColor::Orange;
	case EQuality::EQ_Red:
		return FColor::Red;
	default:
		return FColor::White;
	}
}

FSlateColor FExploreUtility::GetQualitySlateColor(int Quality)
{
	return FSlateColor(GetQualityColor(static_cast<EQuality>(Quality)));
}

FSlateColor FExploreUtility::GetQualitySlateColor(EQuality Quality)
{
	return FSlateColor(GetQualityColor(Quality));
}
