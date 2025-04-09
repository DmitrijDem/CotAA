// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Structs/Items/FullRandomItemSpawn.h"
#include "./Structs/Items/RarityChance.h"
#include "RandomItemSpawn.generated.h"
/**
* Struct to describe Random item spawn properties
**/

USTRUCT(BlueprintType)
struct FFRandomItemSpawn
{
	GENERATED_BODY()

	FFRandomItemSpawn()
		: RandomInSpecificItems(false)
		, RandomItemToSpawn()
		, SpecificItems()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Random In Specific Items?")
	bool RandomInSpecificItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Random Item To Spawn")
	FFFullRandomItemSpawn RandomItemToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Specific Items")
	TArray<FDataTableRowHandle> SpecificItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Rarity Chance")
	TArray<FFRarityChance> RarityChance;
};
