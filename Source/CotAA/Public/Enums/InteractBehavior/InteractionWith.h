// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**------------------------------ Enumerated to define object which to interact with ------------------------------- **/
// Enumerated to tell how interactable should be handled depending on what it is
// Harvestable - herbs, stone, ores, trees, bushes etc. which player "can harvest"
// LootItem - loot bags, or loot itself (for example, meat and leather from cows in "Minecraft" or "Diablo" loot bags)
// NPC - NPC (start dialog, give smth, etc.)
// Door - open or close
// CraftStation - open its UI etc.
// Interact() from IInteractable IS REDEFINED INSIDE AActors IMPLEMENTING IT INSIDE THEM!!!
// Nor PlayerCharacter or smth else know what inside it's function, only AActor* implementing IInteractable
UENUM(BlueprintType)
enum class EInteractionWith : uint8
{
	Harvestable UMETA(DisplayName = "Harvestable"),
	LootItem UMETA(DisplayName = "Loot Item"),
	NPC UMETA(DisplayName = "NPC"),
	Door UMETA(DisplayName = "Door"),
	CraftStation UMETA(DisplayName = "Craft Station"),
};