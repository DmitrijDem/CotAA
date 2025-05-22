// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * This enum describes default behaviour of effects in case if it wasn't described in mappings
 **/
UENUM(BlueprintType)
enum class EEffectInteractionRule : uint8
{
	Combine         UMETA(DisplayName = "Combine"),
	Override        UMETA(DisplayName = "Override"),
	Cancel          UMETA(DisplayName = "Cancel"),
	Transform       UMETA(DisplayName = "Transform"),
	RandomSelect    UMETA(DisplayName = "Random Select")
};

