// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBasePotionEffect.h"
#include "StructUtils/UserDefinedStruct.h"
#include "FPostPotionEffect.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EComparisonOperator : uint8
{
 None,
 Equal,
 GreaterThan,
 GreaterThanOrEqual,
 LowerThan,
 LessThanOrEqual,
 NotEqual,
};

USTRUCT(BlueprintType)
struct FPostPotionEffect
{
 GENERATED_BODY()

public:

 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion Effects")
 FBasePotionEffect Effect;

 // Requirement values (for example, FireResistance > 50)
 UPROPERTY(EditAnywhere)
 TMap<EPotionEffectType, float> Thresholds;
 
 UPROPERTY(EditAnywhere)
 TMap<EPotionEffectType, EComparisonOperator> Operator;

 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Potion Effects")
 bool bIsDiscovered = false;
};