// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Enums/ItemProperties/ItemRarity.h"
#include "RarityChance.generated.h"

/**
* Struct to describe RarityChance of the item
**/

USTRUCT(BlueprintType)
struct FFRarityChance
{
	GENERATED_BODY()
	
public:

	FFRarityChance() : Rarity(EItemRarity::Select), Weight(0.0f) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Rarity")
	EItemRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Weight")
	float Weight;


};
