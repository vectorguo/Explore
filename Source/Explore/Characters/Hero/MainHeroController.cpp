// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHeroController.h"

#include "MainHero.h"
#include "MainHeroBlackboard.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Explore/Characters/CharacterSkill/HeroSkillSprint.h"
#include "Explore/NPC/Npc.h"
#include "Explore/UI/WindowWidgetManager.h"

void AMainHeroController::BeginPlay()
{
	Super::BeginPlay();
	
	//获取所属英雄
	OwnerHero = Cast<AMainHero>(GetPawn());
	
	//等待OwnerHero初始化完成再Tick
	PrimaryActorTick.bCanEverTick = true;//OwnerHero->GetSkillManager() != nullptr;
}

void AMainHeroController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	SetShowMouseCursor(true);

	//绑定玩家输入
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AMainHeroController::Sprint);
	InputComponent->BindAction("LeftMouseBtn", IE_Pressed, this, &AMainHeroController::OnLeftMouseBtnDown);
	InputComponent->BindAction("LeftMouseBtn", IE_Released, this, &AMainHeroController::OnLeftMouseBtnUp);
	InputComponent->BindAction("RightMouseBtn", IE_Pressed, this, &AMainHeroController::OnRightMouseBtnDown);
	InputComponent->BindAction("RightMouseBtn", IE_Released, this, &AMainHeroController::OnRightMouseBtnUp);
	InputComponent->BindAction("OpenBackpack", IE_Pressed, this, &AMainHeroController::OnOpenBackpack);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMainHeroController::OnInteract);
	InputComponent->BindAction("ArmOrDisarm", IE_Pressed, this, &AMainHeroController::OnArmOrDisarm);
	
	InputComponent->BindAxis("MoveForward", this, &AMainHeroController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainHeroController::MoveRight);
	InputComponent->BindAxis("Turn", this, &AMainHeroController::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AMainHeroController::AddControllerPitchInput);
	InputComponent->BindAxis("TurnRate", this, &AMainHeroController::TurnAtRate);
	InputComponent->BindAxis("LookUpRate", this, &AMainHeroController::LookUpAtRate);
	InputComponent->BindAxis("Zoom", this, &AMainHeroController::OnCameraZoom);
}

void AMainHeroController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//是否移动
	auto bMovable = !FMath::IsNearlyZero(MoveForwardValue) || !FMath::IsNearlyZero(MoveRightValue);

	//技能数据
	auto* SkillManager = OwnerHero->GetSkillManager();
	auto* CurrentSkill = SkillManager->GetCurrentSkill();
	if (CurrentSkill && bMovable)
	{
		bMovable = CurrentSkill->IsUnlock();
		if (bMovable)
		{
			CurrentSkill->Stop();
			CurrentSkill = nullptr;
			SkillManager->SetCurrentSkill(nullptr);
		}
	}

	if (bMovable)
	{
		//计算当前Controller在世界坐标下的X轴朝向
		const FRotator Rotation1 = GetControlRotation();
		const FRotator YawRotation1(0.0f, Rotation1.Yaw, 0.0f);
		FVector Direction = FRotationMatrix(YawRotation1).GetUnitAxis(EAxis::X) * MoveForwardValue;

		//计算当前Controller在世界坐标下的Y轴朝向
		const FRotator Rotation2 = GetControlRotation();
		const FRotator YawRotation2(0.0f, Rotation2.Yaw, 0.0f);
		Direction += FRotationMatrix(YawRotation2).GetUnitAxis(EAxis::Y) * MoveRightValue;

		//依据Controller的Y轴朝向移动
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, OwnerHero->GetActorLocation() + Direction * 20);
	}
	else
	{
		if (!CurrentSkill && bIsPressingLeftMouseBtn)
		{
			//连续攻击
			SkillManager->ReleaseValidPassiveSkill();
		}
	}
}

void AMainHeroController::OnSkillEnd()
{
	// auto* SkillManager = OwnerHero->GetSkillManager();
	// SkillManager->StopCurrentSkill();
	//
	// if (bIsPressingLeftMouseBtn)
	// {
	// 	//当前没有释放技能
	// 	if (auto* Skill = SkillManager->PickValidPassiveSkill())
	// 	{
	// 		Skill->Release();
	// 		SkillManager->SetCurrentSkill(Skill);
	// 	}
	// }
}

void AMainHeroController::MoveForward(float Value)
{
	MoveForwardValue = Value;
}

void AMainHeroController::MoveRight(float Value)
{
	MoveRightValue = Value;
}

void AMainHeroController::AddControllerPitchInput(float Val)
{
	if (Val != 0.f)
	{
		AddPitchInput(Val);
	}
}

void AMainHeroController::AddControllerYawInput(float Val)
{
	if (Val != 0.f)
	{
		AddYawInput(Val);
	}
}

void AMainHeroController::TurnAtRate(float Value)
{
	const auto DeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Value * BaseTurnRate * DeltaTime);
}

void AMainHeroController::LookUpAtRate(float Value)
{
	const auto DeltaTime = GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(Value * BaseTurnRate * DeltaTime);
}

void AMainHeroController::OnCameraZoom(float Value)
{
	if (OwnerHero)
	{
		OwnerHero->AddCameraArmLength(Value);
	}
}

void AMainHeroController::Sprint()
{
	auto* SkillManager = OwnerHero->GetSkillManager();
	auto* SprintSkill = Cast<UHeroSkillSprint>(SkillManager->GetActiveSkill(4));
	if (SprintSkill == nullptr || !SprintSkill->IsValid())
	{
		return;
	}

	//停止之前的技能
	SkillManager->StopCurrentSkill();
	
	//计算冲刺方向
	const FRotator Rotation = OwnerHero->GetActorRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	const FVector SprintDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	//释放冲刺
	SprintSkill->SetSprintDirection(SprintDirection);
	SprintSkill->Release();
	SkillManager->SetCurrentSkill(SprintSkill);
}

void AMainHeroController::OnLeftMouseBtnDown()
{
	bIsPressingLeftMouseBtn = true;
	
	//检测当前是否正在释放技能
	auto* SkillManager = OwnerHero->GetSkillManager();
	if (SkillManager->GetCurrentSkill())
	{
		return;
	}
	
	//当前没有释放技能
	SkillManager->ReleaseValidPassiveSkill();
}

void AMainHeroController::OnLeftMouseBtnUp()
{
	bIsPressingLeftMouseBtn = false;
}

void AMainHeroController::OnRightMouseBtnDown()
{
	bIsPressingRightMouseBtn = true;
}

void AMainHeroController::OnRightMouseBtnUp()
{
	bIsPressingRightMouseBtn = false;
}

void AMainHeroController::OnOpenBackpack()
{
	auto* WindowManager = FWindowWidgetManager::GetInstance();
	if (!WindowManager->IsWindowOpened(EWindowWidgetID::EWWT_HeroInfo))
	{
		WindowManager->OpenWindow(EWindowWidgetID::EWWT_HeroInfo);
	}
}

void AMainHeroController::OnInteract()
{
	if (auto* Npc = OwnerHero->GetBlackboard()->GetInteractiveNpc())
	{
		Npc->Interact();
	}
}

void AMainHeroController::OnArmOrDisarm()
{
	if (OwnerHero)
	{
		if (OwnerHero->HasArmedWeaponFacade())
		{
			OwnerHero->DisarmWeaponFacade();
		}
		else
		{
			OwnerHero->ArmWeaponFacade();
		}
	}
}
