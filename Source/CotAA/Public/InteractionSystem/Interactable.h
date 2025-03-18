// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

/* ------------------------------ Enumerated to define interaction type ------------------------------- */
// Enumerated to tell how interactable should be handled
// Press - on button pressed (IA started\ended) - call Interact()
// Hold - on some time button being holded - call Interact()
UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	Press UMETA(DisplayName = "Press"),
	Hold UMETA(DisplayName = "Hold"),
};

/* ------------------------------ Class Definition ------------------------------- */
// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/* ---------------------------- Interface Definition ----------------------------- */

/**
 * Interactable Component Interface. Receives calls from an Interactor component
 */
class COTAA_API IInteractable
{
	GENERATED_BODY()

public:

	// Interaction method. Should be called only by an Interactor Component when input action is pressed, once.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction System handlig")
	void Interact(AActor* Interactor);

	// Returns EInteractableType to tell which interaction type is needed to interact with object
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction System handlig")
	EInteractableType GetInteractionType();
	// Returns EInteractableType to tell which interaction type is needed to interact with object
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction System handlig")
	float GetHoldDuration();
};
