// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COTAADEV_API IPlayerControllerInterface
{
	GENERATED_BODY()

public:

	// Returns EInteractWith to tell WHAT player interacts (NPC, loot, container, etc.)
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interactable properties")
	void ToggleInGameMenu();
};
