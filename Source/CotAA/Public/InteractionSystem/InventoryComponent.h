// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/Items/InventoryItem.h"
#include "InventoryComponent.generated.h"

struct InventoryItem;

USTRUCT(BlueprintType)
struct FHasItem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool bSuccess = false;

	UPROPERTY(BlueprintReadWrite)
	FInventoryItem InventoryItem;

	UPROPERTY(BlueprintReadWrite)
	int32 ItemCount = -1;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COTAADEV_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	UInventoryComponent();

	/** -------------------------- Variables ----------------------------- **/	
	// Array of items on player ("inside his backpack")
	// Basically - all items go into this inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryItem> LocalInventory;

	// Array of items on player's base ("inside his camp, village")
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInventoryItem> GlobalInventory;

	// Hot bar map
	// Key = "button on keyboard"
	// item = "Index inside LocalInventory"
	// Cons of TMap - logic (for me, 1-8 on keyboard === key)
	// Scalable, I can, by default, make it 2-4 slots only and make it bigger in game on player upgrades for example
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<uint8, uint8> Hotbar;
		
	/** -------------------------- Variables end ----------------------------- **/

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ReOrganizeInventory();
	
	UFUNCTION(BlueprintCallable)
	void AddItem(FDataTableRowHandle ItemInfo);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(FDataTableRowHandle ItemInfo, int Amount);

	UFUNCTION(BlueprintPure)
	FHasItem HasItem( FDataTableRowHandle ItemDataTable);

	UFUNCTION(BLueprintPure)
	static bool CompareDataTables(const FDataTableRowHandle& DataTable, const FDataTableRowHandle& CompareWith);
};
