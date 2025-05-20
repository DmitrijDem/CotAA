// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characteristics/CharacterStatsComponent.h"
#include "Characteristics/Damageable.h"
#include "GameFramework/Character.h"
#include "Characteristics/CharacterStatsComponent.h"
#include "Components/BoxComponent.h"
#include "EnemyBase.generated.h"

USTRUCT(BlueprintType)
struct FEnemyStats
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor = 0.0f;

	// Resistances are declared in PlayerStats - create outer file for stats for both player and NPCs
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FResistanceStats ResistanceModifiers;
	// It is possible to add stamina to enemies, so they will have stuns ("Sekiro/Elden Ring-like")
};

UCLASS()
class COTAADEV_API AEnemyBase : public ACharacter, public IDamageable
{
	GENERATED_BODY()

public:

	AEnemyBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	UCharacterStatsComponent* CharacterStats;

	virtual void OnAttackHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void TakeDamage_Implementation(float Damage, const UDamageType* DamageType, AActor* DamageCauser);
	virtual float GetHealth_Implementation() {return FMath::Min(CharacterStats->CurrentStats.Health, 0.0f);};
	virtual void OnDeath_Implementation();
	
	UFUNCTION(BlueprintCallable, Category="Enemy")
	virtual void Attack();

	UFUNCTION(BlueprintCallable, Category="Enemy")
	virtual void UpdateWalkSpeed(float NewWalkSpeed);
	
	UPROPERTY(VisibleAnywhere, Category="Combat")
	UBoxComponent* AttackHitBox;

	private:
	void SetupStarterComponents();
		
};
