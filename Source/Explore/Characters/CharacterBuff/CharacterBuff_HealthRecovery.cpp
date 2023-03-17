// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBuff_HealthRecovery.h"

#include "Explore/Characters/ExploreCharacter.h"
#include "Explore/Characters/CharacterAttribute/CharacterAttribute.h"

void UCharacterBuff_HealthRecovery::Initialize(int32 ID, AExploreCharacter* BuffOwner, AExploreCharacter* BuffCauser, const FTableBuffRowData* BuffConfig)
{
	Super::Initialize(ID, BuffOwner, BuffCauser, BuffConfig);
	
	if (BuffConfig->Params.Num() >= 2)
	{
		RecoveryIntervalTime = BuffConfig->Params[0];
		RecoveryValue = BuffConfig->Params[1];
		bIsPercent = static_cast<bool>(BuffConfig->Params[2]);
	}
	else
	{
		RecoveryIntervalTime = 1;
		RecoveryValue = 0;
		bIsPercent = false;
	}
}

void UCharacterBuff_HealthRecovery::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BuffState != EBuffState::EBS_Finished)
	{
		CurrentIntervalTime += DeltaTime;
		if (CurrentIntervalTime >= RecoveryIntervalTime)
		{
			CurrentIntervalTime -= RecoveryIntervalTime;
			if (bIsPercent)
			{
				//按最大血量百分比恢复当前血量
				const auto MaxHp = Owner->GetAttribute()->GetMaxHealth();
				Owner->GetAttribute()->ModifyHealth(MaxHp * RecoveryValue / 100.0f);
			}
			else
			{
				//恢复具体血量
				Owner->GetAttribute()->ModifyHealth(RecoveryValue);
			}
		}
	}
}
