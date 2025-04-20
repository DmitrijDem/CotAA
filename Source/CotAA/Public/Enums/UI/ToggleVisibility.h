// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToggleVisibility.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EToggleVisibility : uint8
{
	Visible UMETA(DisplayName = "Visible"),
	Hidden UMETA(DisplayName = "Hidden"),
};

