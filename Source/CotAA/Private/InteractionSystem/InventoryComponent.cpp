// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem/InventoryComponent.h"

#include "FunctionLibraries/InventoryKitFL.h"
#include "./Structs/Items/InventoryItem.h"
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

void UInventoryComponent::AddItem(FDataTableRowHandle ItemInfo)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Adding item");
	
}

void UInventoryComponent::RemoveItem(FDataTableRowHandle ItemInfo, int Amount)
{
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Removing item");
}

FHasItem UInventoryComponent::HasItem(FDataTableRowHandle ItemDataTable)
{
	bool LocValid = false;
	FInventoryItem  LocInventoryItem;
	int32 LocIndex = 0;
	
	if (LocalInventory.Num() != 0)
	{		
		for (int32 i = 0; i < LocalInventory.Num(); i++)
		{
			const FInventoryItem& InventoryItem = LocalInventory[i];
			if (CompareDataTables(InventoryItem.MasterItemDataTable, ItemDataTable))
			{
				LocValid = true;
				LocInventoryItem = InventoryItem;
				LocIndex = i;
				break;
			}
			else
			{
				LocValid = false;
			}
		}
	}

	LocValid = false;
	return {LocValid, LocInventoryItem, LocIndex};
}

bool UInventoryComponent::CompareDataTables(const FDataTableRowHandle& DataTable, const FDataTableRowHandle& CompareWith)
{
	return ((DataTable.DataTable == CompareWith.DataTable) && (DataTable.RowName == CompareWith.RowName));
}

TArray<FInventoryItem> UInventoryComponent::RequestBackpackItems()
{
	return LocalInventory;
}

TArray<FInventoryItem> UInventoryComponent::RequestCampItems()
{
	return CampInventory;
}
