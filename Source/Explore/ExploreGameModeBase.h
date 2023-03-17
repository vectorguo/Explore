// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExploreGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EXPLORE_API AExploreGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AExploreGameModeBase();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UIWidget")
	TSubclassOf<class UUserWidget> MainWindowAsset;

	UPROPERTY()
	class UUserWidget* MainWindow;
};
