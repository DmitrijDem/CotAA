// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem/InventoryComponent.h"
#include "InteractionSystem/InventoryComponent.h"
#include "InteractionSystem/InventoryComponent.h"
#include "FunctionLibraries/InventoryKitFL.h"
#include "Structs/Items/InventoryItem.h"
#include "Structs/Items/PotionMaterials/PotionMaterialMasterInfo.h"
// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	ReOrganizeInventory();
}

void UInventoryComponent::ReOrganizeInventory_Implementation()
{
	// Sorting items from rarest for local inventory
	LocalInventory = UInventoryKitFL::SortItemsByRarity(LocalInventory, true);

	// Sorting items from rarest for "camp" inventory
	CampInventory = UInventoryKitFL::SortItemsByRarity(CampInventory, true);
}

void UInventoryComponent::OnInventoryOpened_Implementation()
{
	ReOrganizeInventory();
}

void UInventoryComponent::AddItem(FDataTableRowHandle ItemInfo, EInventoryType TargetInventory)
{

	if (ItemInfo.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("AddItem: ItemInfo is invalid!"));
		return;
	}

	FItemMasterInfo* LocInventoryItem = ItemInfo.GetRow<FItemMasterInfo>(TEXT("AddItem"));
	if (!LocInventoryItem)
	{
		UE_LOG(LogTemp, Error, TEXT("AddItem: Failed to find row in DataTable!"));
		return;
	}

	auto& Inventory = RequestInventoryArray(TargetInventory);

	switch (LocInventoryItem->ItemType)
	{
	case EItemType::Select :
			break;
	case EItemType::Gear:
	case EItemType::QuestItem :
	case EItemType::Document :
			// if player DOESN'T have the same Item
			// Used because these items are not stackable (for now at least)
			if (!(HasItem(TargetInventory, ItemInfo).bSuccess))
			{
				// Directly add item to inventory
				
				Inventory.Add(FInventoryItem(ItemInfo));
			}
			break;
		//  Stackable items - check if they exist and + quantity or create new if they don't
	case EItemType::TradeGood:
		{
			auto Result = HasItem(TargetInventory, ItemInfo);

			if (Result.bSuccess)
			{
				if (IsValid(ItemInfo.DataTable))
				{
					auto TableRow = ItemInfo.DataTable->FindRow<FItemMasterInfo>(ItemInfo.RowName,TEXT("GetInventoryItemInfo"),true);
					FTradeGoodMasterInfo TradeGoodInfo = UInventoryKitFL::GetItemInfoAsTradeGoods(*TableRow);
					Result.InventoryItem.EditableInfo.Amount += TradeGoodInfo.Amount;
					Inventory[Result.Index] = Result.InventoryItem;
				}
			}
			else
			{
				FTradeGoodMasterInfo TradeGoodInfo = UInventoryKitFL::GetItemInfoAsTradeGoods(*LocInventoryItem);
				int Index = Inventory.Add(FInventoryItem(ItemInfo));
				Inventory[Index] = FInventoryItem(TradeGoodInfo.Amount);
			}
			break;
		}
	case EItemType::PotionMaterial:
		{
			auto Result = HasItem(TargetInventory, ItemInfo);

			if (Result.bSuccess)
			{
				if (IsValid(ItemInfo.DataTable))
				{
					auto TableRow = ItemInfo.DataTable->FindRow<FItemMasterInfo>(ItemInfo.RowName,TEXT("GetInventoryItemInfo"),true);
					FPotionMaterialMasterInfo PotionMaterialInfo = UInventoryKitFL::GetItemInfoAsPotionMaterial(*TableRow);
					Result.InventoryItem.EditableInfo.Amount += PotionMaterialInfo.Amount;
					Inventory[Result.Index] = Result.InventoryItem;
				}
			}
			else
			{
				FPotionMaterialMasterInfo PotionMaterialInfo = UInventoryKitFL::GetItemInfoAsPotionMaterial(*LocInventoryItem);
				FItemEditableInfo EditableInfo;
				EditableInfo.Amount = PotionMaterialInfo.Amount;

				FInventoryItem NewItem(ItemInfo, EditableInfo);
				int32 Index = Inventory.Add(NewItem);
			}
			break;
		}
	}
}	


void UInventoryComponent::RemoveItem(FDataTableRowHandle ItemInfo, int Amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Removing item");
}

FHasItem UInventoryComponent::HasItem(EInventoryType TargetInventory, const FDataTableRowHandle& ItemDataTable)
{
	FHasItem Result;
	auto& Inventory = RequestInventoryArray(TargetInventory);

	if (Inventory.Num() == 0)
	{
		return Result;
	}

	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		const FInventoryItem& InventoryItem = Inventory[i];
		if (CompareDataTables(InventoryItem.MasterItemDataTable, ItemDataTable))
		{
			Result.bSuccess = true;
			Result.InventoryItem = InventoryItem;
			Result.Index = i;
			break;
		}
	}

	return Result;
}

bool UInventoryComponent::CompareDataTables(const FDataTableRowHandle& DataTable, const FDataTableRowHandle& CompareWith)
{
	return ((DataTable.DataTable == CompareWith.DataTable) && (DataTable.RowName == CompareWith.RowName));
}

TArray<FInventoryItem>& UInventoryComponent::RequestInventoryArray(EInventoryType TargetInventory)
{
	switch (TargetInventory)
	{
	case EInventoryType::Backpack: return LocalInventory;
	case EInventoryType::Camp : return CampInventory;
		default:
			UE_LOG(LogTemp, Warning, TEXT("InventoryComponent.cpp: No handler for this type of the inventory, return player's BackpackInventory(Local)"));
		return LocalInventory;
	}
}