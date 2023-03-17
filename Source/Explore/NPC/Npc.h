// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Npc.generated.h"

UCLASS()
class EXPLORE_API ANpc : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANpc();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	/**
	 * @brief 交互
	 */
	virtual void Interact()
	{
		
	}
	
protected:
	/**
	 * @brief 骨骼Mesh
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NPC | Mesh")
	class USkeletalMeshComponent* Mesh;

	/**
	 * @brief 碰撞盒
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="NPC | Collision")
	class USphereComponent* CollisionVolume;

	/**
	 * @brief UIWidget
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC | UI")
	class UWidgetComponent* WidgetComponent;
};
