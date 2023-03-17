// Fill out your copyright notice in the Description page of Project Settings.

#include "ExploreCharacter.h"

#include "CharacterAttribute/CharacterAttribute.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Explore/UI/WindowWidgetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AExploreCharacter::AExploreCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//创建UI Widget
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("UIWidget"));
	WidgetComponent->SetupAttachment(GetRootComponent());
}

AExploreCharacter::~AExploreCharacter()
{
}

void AExploreCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//设置移动参数
	auto* Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (Movement)
	{
		Movement->bOrientRotationToMovement = true;
		Movement->RotationRate = FRotator(0, 720.0f, 0);
		Movement->JumpZVelocity = 650.0f;
		Movement->AirControl = 0.2f;
		
		Movement->GravityScale = 0.0f;
		Movement->bUseRVOAvoidance = true;
		Movement->bEnablePhysicsInteraction = false;
		Movement->MovementState.bCanJump = false;
		Movement->MovementState.bCanCrouch = false;
		Movement->MovementState.bCanFly = false;
		Movement->MovementState.bCanSwim = false;
		Movement->SetUpdateNavAgentWithOwnersCollisions(false);
		Movement->SetGroundMovementMode(EMovementMode::MOVE_NavWalking);
	}

	//初始化碰撞(必须在设置Movement参数后，否则Movement会重置胶囊碰撞参数)
	if (auto* CapsuleCollision = GetCapsuleComponent())
	{
		CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	//创建属性
	if (AttributeClass)
	{
		//创建属性
		Attribute = NewObject<UCharacterAttribute>(this, AttributeClass, TEXT("Attribute"));
	}
	else
	{
		//创建属性
		Attribute = NewObject<UCharacterAttribute>(this, TEXT("Attribute"));
	}
	Attribute->Initialize();

	//添加Buff,Skill,State组件
	BuffManager = NewObject<UCharacterBuffComponent>(this, TEXT("BuffManager"));
	BuffManager->RegisterComponent();
	SkillManager = NewObject<UCharacterSkillComponent>(this, TEXT("SkillManager"));
	SkillManager->RegisterComponent();

	//重新获取WidgetComponent（不确定什么原因导致在BeginPlay里WidgetComponent会变成空指针，需要重新获取）
	WidgetComponent = Cast<UWidgetComponent>(GetComponentByClass(UWidgetComponent::StaticClass()));

	//通知Controller更新
	if (Controller)
	{
		Controller->PrimaryActorTick.bCanEverTick = true;
	}
}

void AExploreCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AExploreCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	auto DamagePosition = GetActorLocation();
	if (const auto* Capsule = GetCapsuleComponent())
	{
		DamagePosition.Z += Capsule->GetScaledCapsuleHalfHeight() + 10.0f;
	}
	FWindowWidgetManager::GetInstance()->PlayDamagePopup(DamageAmount, DamagePosition);
	return DamageAmount;
}

void AExploreCharacter::PlayMontage(const FName& SectionName, const float PlayRate)
{
	if (AnimMontage)
	{
		auto* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Play(AnimMontage, PlayRate);
			AnimInstance->Montage_JumpToSection(SectionName, AnimMontage);
		}
	}
}

void AExploreCharacter::PauseMontage()
{
	if (AnimMontage)
	{
		auto* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Pause(AnimMontage);
		}
	}
}

void AExploreCharacter::StopMontage(float InBlendOutTime)
{
	if (AnimMontage)
	{
		auto* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->Montage_Stop(InBlendOutTime, AnimMontage);
		}
	}
}

void AExploreCharacter::AttachEffect(AActor* Effect, const FName& SocketName, bool bFromTimeline)
{
	if (!Effect)
	{
		return;
	}
	
	if (const auto* Socket = GetMesh()->GetSocketByName(SocketName))
	{
		Socket->AttachActor(Effect, GetMesh());
		Effects.Emplace(Effect);
	}
}

void AExploreCharacter::DetachEffect(AActor* Effect)
{
	auto Index = Effects.IndexOfByKey(Effect);
	if (Index != INDEX_NONE)
	{
		Effect->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Effects.RemoveAtSwap(Index);
	}
}

void AExploreCharacter::SetVisible(bool Visible, bool bIncludeTick)
{
	SetActorHiddenInGame(!Visible);
	SetActorEnableCollision(Visible);

	if (bIncludeTick)
	{
		SetActorTickEnabled(Visible);
	}
}

void AExploreCharacter::SetWidgetVisible(bool Visible)
{
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(Visible);
	}
}

void AExploreCharacter::Die()
{
	SetWidgetVisible(false);

	//停止当前技能
	SkillManager->StopCurrentSkill();
}

void AExploreCharacter::OnDeathEnd()
{
}

void AExploreCharacter::Revive()
{
	Attribute->Reset();
	
	//设置可见
	SetVisible(true, true);
}
