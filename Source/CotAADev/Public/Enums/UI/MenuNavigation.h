// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuNavigation.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMenuNavigation : uint8
{
	Select UMETA(DisplayName = "Select"),
	Previous UMETA(DisplayName = "Previous"),
	Next UMETA(DisplayName = "Next"),
};
