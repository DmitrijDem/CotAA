// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/Items/Potions/PotionMaterial.h"
#include "FPotionLayer.generated.h"

/**
 * struct to describe potion layer in creation UI
 */
USTRUCT(BlueprintType)
struct COTAADEV_API FPotionLayer
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Alchemy|Brewing")
	TArray<FPotionMaterial> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Alchemy|Brewing")
	TMap<EPotionEffectType, float> CombinedEffects;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Alchemy|Brewing")
	float LayerToxicity = 0.0f;
};
