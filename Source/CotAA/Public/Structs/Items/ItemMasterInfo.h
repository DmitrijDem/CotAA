// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemInfo.h"
#include "Enums/ItemProperties/ItemType.h"
#include "ItemMasterInfo.generated.h"

/**
 * Struct to use inside of Data tables to describe all item's info
 * BaseItemInfo- info about item which every item must have - icons, names, descriptions, etc. 
 * ItemDataTable - info about item itself, unique for each item: gear, potion_materials, trade_goods, etc.
 */
USTRUCT(BlueprintType)
struct COTAADEV_API FItemMasterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	FItemMasterInfo()
		   : ItemType(EItemType::Select)
		   , BaseItemInfo()
		   , ItemDataTable()
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Item Type")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Base Item Info")
	FBaseItemInfo BaseItemInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Item's Data Table")
	FDataTableRowHandle ItemDataTable;
};
