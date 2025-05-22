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

UENUM(BlueprintType)
enum class EPotionBehaviorType : uint8
{
	None, // Default value - just create collision sphere and apply effects in radius
	AreaPuddle,		// Creates puddle which will disappear after some time adding effect to anyone entering it
	Spikes,			// Almost same as puddle, but they deal some physical damage by themselves (possibly, some effects might be stronger using this behavior)
	Wall,			// Creates a wall applying effect to anyone near it (almost like in BG3 or D&D)
};

USTRUCT(BlueprintType)
struct FPotionBehavior
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPotionBehaviorType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration;
};

USTRUCT(BlueprintType)
struct COTAA_API FBrewedPotion
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions")
	TArray<FBasePotionEffect> PrimaryEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions")
	TArray<FPostPotionEffect> PostEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions")
	TSet<EPotionEffectType> DiscoveredEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions")
	FPotionBehavior Behavior;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions")
	float TotalToxicity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potions", meta=(Bitmask, BitMaskEnum="./Script/CotAADev.EPotionCraftingFlag")) 
	int32 RequiredFlags;
};
