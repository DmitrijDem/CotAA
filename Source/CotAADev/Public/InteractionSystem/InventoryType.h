// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryType.generated.h"

/**
 * This enum describes inventory of the player, interacting with (used in functions as parameter)
 **/
UENUM(BlueprintType)
enum class EInventoryType : uint8
{
	Select UMETA(DisplayName = "Select"),
	Backpack UMETA(DisplayName = "Backpack"),
	Camp UMETA(DisplayName = "Camp"),
	Temporary UMETA(DisplayName = "Temporary"),
};
