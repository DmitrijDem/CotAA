// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionSystem/InventoryComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structs/Items/InventoryItem.h"
#include "Structs/Items/ItemMasterInfo.h"
#include "Structs/Items/Potions/PotionMaterial.h"
#include "Structs/Items/TradeGoods/TradeGoodMasterInfo.h"
#include "InventoryKitFL.generated.h"

/**
 * Blueprint function library to work with inventory component
 */
USTRUCT(BlueprintType)
struct FHasItemReturnStruct
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bReturnValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInventoryItem InventoryItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index;
	
};

UCLASS(Blueprintable)
class COTAA_API UInventoryKitFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UInventoryComponent* GetInventoryComponent(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static APlayerCharacter* GetPlayerCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static FItemMasterInfo GetInventoryItemInfo(FInventoryItem InventoryItem);

	UFUNCTION(BlueprintCallable)
	static FTradeGoodMasterInfo GetItemInfoAsTradeGoods(FItemMasterInfo InventoryItem);

	UFUNCTION(BlueprintCallable)
	static FPotionMaterial GetItemInfoAsPotionMaterial(const FItemMasterInfo& InventoryItem);

	UFUNCTION(BlueprintCallable)
	static TArray<FInventoryItem>SortItemsByRarity(TArray<FInventoryItem> InventoryItems, bool FromRarest);
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static TArray<FInventoryItem>GetInventoryItems(const UObject* WorldContextObject, EInventoryType TargetInventory);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UCharacterStatsComponent* GetPlayerStatsComponent(const UObject* WorldContextObject);
};
