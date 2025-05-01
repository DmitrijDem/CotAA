// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RandomItemSpawn.h"


/**
* Struct to describe item to spawn (random or not)
**/

USTRUCT(BlueprintType)
struct FFItemToSpawn
{
	GENERATED_BODY()

public:

	FFItemToSpawn(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Random Item?")
	bool RandomItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Random Item To Spawn")
	FFRandomItemSpawn RandomItemToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Specific Items")
	FDataTableRowHandle SpecificItemToSpawn;
};