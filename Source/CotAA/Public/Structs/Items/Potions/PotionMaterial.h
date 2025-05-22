// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Structs/Items/Potions/FBasePotionEffect.h"
#include "./Enums/ItemProperties/MaterialType.h"
#include "PotionMaterial.generated.h"

/**
 * 
 */

UENUM(Blueprintable)
enum class EPotionCraftingFlag : uint8
{
	None,
	UnstableReaction    UMETA(DisplayName = "Unstable Reaction"),         // Random potion mutations
	LunarInfused         UMETA(DisplayName = "Lunar Infusion"),           // If potion is created at night - it gets effect (WIP)
	ParasiticGrowth      UMETA(DisplayName = "Parasitic Growth"),         // One random/special effect from material appears in neighbour layers of potion
};

USTRUCT(BlueprintType)
struct FMaterialEffectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsDiscovered = false;
};

USTRUCT(BlueprintType)
struct FPotionMaterial : public FTableRowBase
{
	GENERATED_BODY()

	public:
	// Information to categorize material (for future sorting items, for example)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMaterialType MaterialType = EMaterialType::Select;
	
	// Tags describe "which" effects material carries on it and which will be applied when material is being used
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EPotionEffectType, FMaterialEffectData> AllEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<EPotionCraftingFlag> CraftingFlags;
	
	// Value to add to "Toxicity" meter of the player (not applied to any enemies)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Toxicity = 0.0f;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading Info")
	int32 Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trading Info")
	int ValueAsCoin;
};
