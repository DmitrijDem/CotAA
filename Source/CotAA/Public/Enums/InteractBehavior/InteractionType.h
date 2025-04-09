// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**------------------------------ Enumerated to define interaction type ------------------------------- **/
// Enumerated to tell how interactable should be handled
// Press - on button pressed (IA started\ended) - call Interact()
// Hold - on some time button being holded - call Interact()
UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	Press UMETA(DisplayName = "Press"),
	Hold UMETA(DisplayName = "Hold"),
};
