// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/InteractBehavior/InteractionType.h"
#include "Enums/InteractBehavior/InteractionWith.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

/**------------------------------ Forward Declaration ------------------------------- **/
class UInventoryComponent;
/**------------------------------ Class Definition ------------------------------- **/
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**---------------------------- Interface Definition ----------------------------- **/

/**
 * Interactable Component Interface. Receives calls from an Interactor component
 **/
class COTAA_API IInteractable
{
	GENERATED_BODY()


public:
	// Interaction method. Should be called only by an Interactor  when input action, once.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction System handlig")
	void Interact(AActor* Interactor);

	// Function I created in case I need to separate interactions
	// Interaction method for loot. Should be called only by an Interactor when input action, once.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction System handlig")
	void InteractLootable(AActor* Interactor);

	// Returns EInteractableType to tell which interaction type is needed to interact with object
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable properties")
	EInteractableType GetInteractionType();

	// Returns EInteractWith to tell WHAT player interacts (NPC, loot, container, etc.)
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable properties")
	EInteractionWith GetInteractWith();
	
	// Returns EInteractableType to tell which interaction type is needed to interact with object
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable properties")
	float GetHoldDuration();
};
