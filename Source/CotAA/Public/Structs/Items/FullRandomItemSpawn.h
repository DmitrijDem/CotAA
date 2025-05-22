// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemProperties/ItemType.h"
#include "FullRandomItemSpawn.generated.h"
/**
* Struct to describe Full Random item to spawn
**/

USTRUCT(BlueprintType)
struct FFFullRandomItemSpawn
{
	GENERATED_BODY()

public:

	FFFullRandomItemSpawn()
	{
		CheckItemType = false;
		ItemType = EItemType::Select;
		AllItemsDataTable = nullptr;
	}

	// True if needed to check item type, false - don't
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Check Item Type")
	bool CheckItemType;

	// Type of the item (gear, weapon, material, potion, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Item Type")
	EItemType ItemType;
	// Items Data Table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "All Items Data Table")
	UDataTable* AllItemsDataTable;

};
