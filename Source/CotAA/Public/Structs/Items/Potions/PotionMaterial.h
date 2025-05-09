// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Structs/Items/Potions/FBasePotionEffect.h"
#include "./Enums/ItemProperties/MaterialType.h"
#include "PotionMaterial.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPotionMaterial : public FTableRowBase
{
	GENERATED_BODY()

	public:
	// Information to categorize material (for future sorting items, for example)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMaterialType MaterialType = EMaterialType::Select;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	// Tags describe "which" effects material carries on it and which will be applied when material is being used
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum = "EPotionEffectType"))
	int32 EffectTags;

	// "Base" power of the effects in material (in points - for creating potions)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPotionEffectType, float> EffectsPower;

	// Value to add to "Toxicity" meter of the player (not applied to any enemies)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Toxicity = 0.0f;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading Info")
	int Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading Info")
	int ValueAsCoin;
};
