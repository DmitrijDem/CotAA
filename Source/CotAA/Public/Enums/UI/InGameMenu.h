// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EInGameMenu : uint8
{
	Inventory UMETA(DisplayName = "Inventory"),
	Quests UMETA(DisplayName = "Quests"),
	WorldMap UMETA(DisplayName = "World Map"),
	Skills UMETA(DisplayName = "Skills"),
};
