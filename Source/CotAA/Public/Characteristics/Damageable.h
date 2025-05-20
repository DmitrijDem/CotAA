// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

UINTERFACE(BlueprintType)
class COTAADEV_API UDamageable : public UInterface
{
	GENERATED_BODY()
};

class COTAADEV_API IDamageable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category ="Damage")
	void TakeDamage(float Damage, const UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Damage")
	float GetHealth();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Damage")
	void OnDeath();
};
