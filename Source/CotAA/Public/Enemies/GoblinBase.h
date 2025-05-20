// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBase.h"
#include "AIController.h"
#include "GoblinBase.generated.h"

/**
 * Called GoblinBase - because it is supposed to be parent-class for any goblin - archers, spears, sword etc.
 * For prototype purposes it will be SINGLE class for any goblin
 *
 * I will create independent controllers for both goblin prototype and skeleton - I don't know how it must be and don't have time to find out 
 */

UCLASS()
class COTAADEV_API AGoblinAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	private:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree* BehaviorTree;
};

UCLASS()
class COTAADEV_API AGoblinBase : public AEnemyBase
{
	GENERATED_BODY()

public:
	AGoblinBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enemy|Goblin")
	float AttackRange = 150.0f;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void OnAttackHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void Attack() override;
};
