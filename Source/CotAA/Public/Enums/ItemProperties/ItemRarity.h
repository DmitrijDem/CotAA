// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *  Enum to describe item rarity
 */
UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Select UMETA(DisplayName = "Select"),
	Common UMETA(DisplayName = "Common"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
	Relics UMETA(DisplayName = "Relic"),	
};
