#include "WindowWidgetManager.h"

#include "HeroInfoWindowWidget.h"
#include "DamagePopupWidget.h"
#include "EquipmentInfoWindowWidget.h"
#include "ForgerWindowWidget.h"
#include "ItemInfoWindowWidget.h"
#include "MainWindowWidget.h"
#include "ShopWindowWidget.h"
#include "Explore/ExploreGameManager.h"
#include "Explore/Characters/Hero/MainHero.h"

FWindowWidgetManager::FWindowWidgetManager()
{
}

FWindowWidgetManager::~FWindowWidgetManager()
{
	//清空窗口列表，防止重复运行时静态数据残留
	Windows.Empty();
}

FWindowWidgetManager* FWindowWidgetManager::GetInstance()
{
	static FWindowWidgetManager* Instance = new FWindowWidgetManager();
	return Instance;
}

void FWindowWidgetManager::Initialize(UWorld* World)
{
	WindowOwner = World;

	//清空窗口列表，防止重复运行时静态数据残留
	Windows.Empty();

	//加载伤害数字class
	const auto DamagePopupBPPath = FString(TEXT("/Game/Blueprints/UI/BP_UI_DamagePopup.BP_UI_DamagePopup_C"));
	DamagePopupClass = LoadClass<UUserWidget>(nullptr, *DamagePopupBPPath);
}

UWindowWidget* FWindowWidgetManager::OpenWindow(EWindowWidgetID ID)
{
	UWindowWidget* Window;
	switch (ID)
	{
		case EWindowWidgetID::EWWT_Main:
		{
			UClass* WindowWidget = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/BP_UI_MainWindow.BP_UI_MainWindow_C"));
			Window = CreateWidget<UMainWindowWidget>(WindowOwner, WindowWidget);
			break;
		}
		case EWindowWidgetID::EWWT_HeroInfo:
		{
			UClass* WindowWidget = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/BP_UI_HeroInfoWindow.BP_UI_HeroInfoWindow_C"));
			Window = CreateWidget<UHeroInfoWindowWidget>(WindowOwner, WindowWidget);
			break;
		}
		case EWindowWidgetID::EWWT_EquipmentInfo:
		{
			UClass* WindowWidget = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/BP_UI_EquipmentInfo.BP_UI_EquipmentInfo_C"));
			Window = CreateWidget<UEquipmentInfoWindowWidget>(WindowOwner, WindowWidget);
			break;
		}
		case EWindowWidgetID::EWWT_ItemInfo:
		{
			UClass* WindowWidget = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/BP_UI_ItemInfo.BP_UI_ItemInfo_C"));
			Window = CreateWidget<UItemInfoWindowWidget>(WindowOwner, WindowWidget);
			break;
		}
		case EWindowWidgetID::EWWT_Forger:
		{
			UClass* WindowWidget = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/BP_UI_Forger.BP_UI_Forger_C"));
			Window = CreateWidget<UForgerWindowWidget>(WindowOwner, WindowWidget);
			break;
		}
		case EWindowWidgetID::EWWT_Shop:
		{
			UClass* WindowWidget = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/UI/BP_UI_Shop.BP_UI_Shop_C"));
			Window = CreateWidget<UShopWindowWidget>(WindowOwner, WindowWidget);
			break;
		}
		default:
			Window = nullptr;
	}
	
	if (Window)
	{
		Window->AddToViewport();

		//处理输入
		SetGameInputEnabled(Window->AllowGameInput());
		
		//处理窗口堆栈
		if (!Windows.IsEmpty())
		{
			auto* TopWindow = Windows.Last();
			switch (Window->GetWindowType())
			{
				case EWindowWidgetType::EWWT_Main:
				case EWindowWidgetType::EWWT_Generic:
					TopWindow->Hide();
					break;
				default:
					break;
			}
		}
		Windows.Emplace(Window);
	}
	
	return Window;
}

void FWindowWidgetManager::CloseWindow(EWindowWidgetID ID)
{
	const auto LastIndex = Windows.Num() - 1;
	for (auto Index = LastIndex; Index >= 0; --Index)
	{
		auto* Window = Windows[Index];
		if (Window->GetWindowID() == ID)
		{
			if (Index == LastIndex && (Index - 1 >= 0) && Window->GetWindowType() == EWindowWidgetType::EWWT_Generic)
			{
				auto* NextWindow = Windows[Index - 1];
				NextWindow->Show();

				//处理输入
				SetGameInputEnabled(NextWindow->AllowGameInput());
			}
			Window->RemoveFromParent();
			Windows.RemoveAt(Index);
			break;
		}
	}
}

UWindowWidget* FWindowWidgetManager::GetWindow(EWindowWidgetID ID) const
{
	for (auto Iter = Windows.CreateConstIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetWindowID() == ID)
		{
			return *Iter;
		}
	}
	return nullptr;
}

bool FWindowWidgetManager::IsWindowOpened(EWindowWidgetID ID) const
{
	for (auto Iter = Windows.CreateConstIterator(); Iter; ++Iter)
	{
		if ((*Iter)->GetWindowID() == ID)
		{
			return true;
		}
	}
	return false;
}

void FWindowWidgetManager::PlayDamagePopup(int DamageValue, const FVector& WorldPosition)
{
	if (DamagePopupClass)
	{
		auto* DamagePopup = CreateWidget<UDamagePopupWidget>(WindowOwner, DamagePopupClass);
		DamagePopup->SetDamageValue(DamageValue);
		DamagePopup->SetDesiredSizeInViewport(FVector2D(100, 30));
		DamagePopup->AddToViewport();

		auto* Hero = UExploreGameManager::GetInstance()->GetMainHero();
		if (Hero)
		{
			auto* Controller = Hero->GetController<APlayerController>();
			if (Controller)
			{
				FVector2D ScreenPosition;
				Controller->ProjectWorldLocationToScreen(WorldPosition, ScreenPosition);
				DamagePopup->SetPositionInViewport(ScreenPosition);
			}
		}
	}
}

void FWindowWidgetManager::SetGameInputEnabled(bool bEnabled)
{
	if (bGameInputEnabled == bEnabled)
	{
		return;
	}
	bGameInputEnabled = bEnabled;
	
	auto* MainHero = UExploreGameManager::GetInstance()->GetMainHero();
	if (auto* MainHeroController = MainHero->GetController<APlayerController>())
	{
		if (bEnabled)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(false);
			MainHeroController->SetInputMode(InputMode);
		}
		else
		{
			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			MainHeroController->SetInputMode(InputMode);
		}
	}
}
