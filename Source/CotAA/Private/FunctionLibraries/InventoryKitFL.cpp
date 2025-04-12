// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/InventoryKitFL.h"

UInventoryComponent* UInventoryKitFL::GetInventoryComponent(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		UE_LOG(LogTemp, Error, TEXT("WorldContextObject is null!"));
		return nullptr;
	}

	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get World!"));
		return nullptr;
	}

	APlayerController* PC = World->GetFirstPlayerController();
	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not found!"));
		return nullptr;
	}
	
	if (!PC->IsLocalController() || !PC->IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is not local!"));
		return nullptr;
	}

	APawn* ControlledPawn = PC->GetPawn();
	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ControlledPawn is null!"));
		return nullptr;
	}
	
	UInventoryComponent* InventoryComponent = ControlledPawn->FindComponentByClass<UInventoryComponent>();
	if (!InventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent not found on Pawn!"));
		return nullptr;
	}

	return InventoryComponent;
}

FItemMasterInfo UInventoryKitFL::GetInventoryItemInfo(const FInventoryItem& InventoryItem)
{
	FItemMasterInfo ItemInfo;
	
	if (!InventoryItem.MasterItemDataTable.DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid DataTable reference!"));
		return ItemInfo;
	}

	if (InventoryItem.MasterItemDataTable.RowName.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("RowName is not set!"));
		return ItemInfo;
	}
	
	FItemMasterInfo* RowData = InventoryItem.MasterItemDataTable.DataTable->FindRow<FItemMasterInfo>(
		InventoryItem.MasterItemDataTable.RowName,
		TEXT("GetInventoryItemInfo"),
		true
	);

	if (RowData)
	{
		ItemInfo = *RowData;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Row '%s' not found in DataTable '%s'"), 
			*InventoryItem.MasterItemDataTable.RowName.ToString(),
			*InventoryItem.MasterItemDataTable.DataTable->GetName());
	}

	return ItemInfo;
}
