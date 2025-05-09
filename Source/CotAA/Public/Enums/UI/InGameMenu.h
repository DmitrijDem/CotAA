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
	WorldMap UMETA(DisplayName = "World Map"),
	Quests UMETA(DisplayName = "Quests"),
	Inventory UMETA(DisplayName = "Inventory"),
	Skills UMETA(DisplayName = "Skills"),
};
