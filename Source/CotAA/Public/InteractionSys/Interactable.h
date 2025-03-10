// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact reaction")
	void Interact(AActor* Interactor);
};