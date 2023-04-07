// Fill out your copyright notice in the Description page of Project Settings.


#include "ExploreTimelinePointArmWeaponFacade.h"

#include "Engine/SkeletalMeshSocket.h"
#include <Explore/Characters/CharacterEquipAndItem/CharacterEquipment.h>
#include <Explore/Characters/CharacterEquipAndItem/CharacterEquipmentFacade.h>
#include <Explore/Characters/Hero/MainHero.h>
#include "Explore/Table/TableString.h"
#include "Explore/Timeline/ExploreTimeline.h"

void UExploreTimelinePointArmWeaponFacade::Initialize(const TArray<float>& Params, int32& Index)
{
	Super::Initialize(Params, Index);

	SocketName = FName(FTableString::GetRow(Params[Index++])->Content);
}

void UExploreTimelinePointArmWeaponFacade::Execute(UExploreTimeline* Timeline)
{
	Super::Execute(Timeline);

	if (auto* Character = Timeline->GetCharacter())
	{
		if (auto* MainHero = Cast<AMainHero>(Character))
		{
			if (auto* Weapon = MainHero->GetEquipment(EEquipmentPart::EEP_Weapon))
			{
				if (auto* WeaponFacade = Weapon->GetWeaponFacade())
				{
					if (const auto* Socket = MainHero->GetMesh()->GetSocketByName(SocketName))
					{
						Socket->AttachActor(WeaponFacade, MainHero->GetMesh());
						WeaponFacade->SetActorRelativeScale3D(FVector::OneVector);
					}
				}
			}
		}
	}
}
