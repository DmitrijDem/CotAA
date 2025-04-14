// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionSystem/InventoryComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structs/Items/InventoryItem.h"
#include "Structs/Items/ItemMasterInfo.h"
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

UCLASS()
class COTAADEV_API UInventoryKitFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static UInventoryComponent* GetInventoryComponent(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable)
	static FItemMasterInfo GetInventoryItemInfo(const FInventoryItem& InventoryItem);
	
};
