// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/PotionProperties/PotionEffectType.h"
#include "StructUtils/UserDefinedStruct.h"
#include "FBasePotionEffect.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBasePotionEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion Effects")
	EPotionEffectType EffectType;

	// Power of the effect in "anything" (healing 50 - 50 HP, FireDamage 30 - 30 HP/Sec, Speed 1.2 - 120% etc.) !!! Might be changed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion Effects")
	float Power = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion Effects")
	float Duration = 10.0f;
};
