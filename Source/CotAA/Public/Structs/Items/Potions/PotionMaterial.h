// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Structs/Items/Potions/PotionEffect.h"
#include "PotionMaterial.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPotionMaterial : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy")
	TArray<FPotionEffect> PrimaryEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy")
	TArray<FPotionEffect> SecondaryEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy")
	TArray<FPotionEffect> PostEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy")
	int32 ToxicityPoints = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alchemy")
	bool AdditionalRequirementsToUse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Master Info")
	int Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Master Info")
	int ValueAsCoin;
};
