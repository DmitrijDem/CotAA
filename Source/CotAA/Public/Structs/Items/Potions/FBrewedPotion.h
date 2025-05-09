// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBasePotionEffect.h"
#include "FPostPotionEffect.h"
#include "StructUtils/UserDefinedStruct.h"
#include "FBrewedPotion.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct COTAADEV_API FBrewedPotion
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions")
	TArray<FBasePotionEffect> PrimaryEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions")
	TArray<FPostPotionEffect> PostEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions")
	float TotalToxicity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions", meta=(BitmaskEnum = "EpotionEffectType"))
	int32 RequiredFlags;
};
