// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBasePotionEffect.h"
#include "StructUtils/UserDefinedStruct.h"
#include "FPostPotionEffect.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)

struct FPostPotionEffect
{
 GENERATED_BODY()

public:
 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion Effects")
 EPotionEffectType EffectType;

 // Requirement values (for example, FireResistance > 50)
 UPROPERTY(EditAnywhere)
 TMap<EPotionEffectType, float> Thresholds;;

 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion Effects")
 FBasePotionEffect Effect;
};