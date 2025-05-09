// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MaterialType.generated.h"

/**
 *  Enum to describe item's
 */
UENUM(BlueprintType)
enum class EMaterialType : uint8
{
	Select UMETA(DisplayName = "Select"),
	Herbal UMETA(DisplayName = "Herbal"),
	Mushroom UMETA(DisplayName = "Mushrooms"),
	Mineral UMETA(DisplayName = "Minerals"),
	Animal UMETA(DisplayName = "Animals"),
};

