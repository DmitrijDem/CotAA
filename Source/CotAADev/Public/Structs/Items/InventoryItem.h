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

	FInventoryItem()
	: EditableInfo(), MasterItemDataTable()
	{};
	
	FInventoryItem(const FDataTableRowHandle& pMasterItemDT)
	: EditableInfo(), MasterItemDataTable(pMasterItemDT)
	{};
	
	FInventoryItem(const FItemEditableInfo& pEditableInfo)
	: EditableInfo(pEditableInfo), MasterItemDataTable()
	{};
	
	FInventoryItem(const FDataTableRowHandle& pMasterItemDT, const FItemEditableInfo& pEditableInfo) 
	: MasterItemDataTable(pMasterItemDT), EditableInfo(pEditableInfo) 
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Editable Info")
	FItemEditableInfo EditableInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Master Item Data Table")
	FDataTableRowHandle MasterItemDataTable;

};