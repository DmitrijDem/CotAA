#pragma once

#include "CoreMinimal.h"
#include "ItemEditableInfo.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"
/**
* Struct to describe Full Random item to spawn
**/

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Editable Info")
	FItemEditableInfo InventoryItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Master Item Data Table")
	FDataTableRowHandle MasterItemDataTable;

};