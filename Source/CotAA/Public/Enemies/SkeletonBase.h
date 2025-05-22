// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemyBase.h"
#include "AIController.h"
#include "SkeletonBase.generated.h"

UCLASS()
class COTAA_API ASkeletonAIController : public AAIController
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
class COTAA_API ASkeletonBase : public AEnemyBase
{
	GENERATED_BODY()

public:
	ASkeletonBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Enemy|Goblin")
	float AttackRange = 150.0f;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void OnAttackHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void Attack() override;
};
