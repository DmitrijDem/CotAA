// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraries/InventoryKitFL.h"

#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Tests/AutomationCommon.h"

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

	APawn* ControlledPawn = PC->GetPawn();
	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ControlledPawn is null!"));
		return nullptr;
	}
	
	if (!PC->IsLocalController() || !PC->IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is not local!"));
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

APlayerCharacter* UInventoryKitFL::GetPlayerCharacter(const UObject* WorldContextObject)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APlayerCharacter::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		return Cast<APlayerCharacter>(FoundActors[0]);
	}

	return nullptr;
}

FItemMasterInfo UInventoryKitFL::GetInventoryItemInfo(FInventoryItem InventoryItem)
{
	FItemMasterInfo ItemInfo;
	
	if (!InventoryItem.MasterItemDataTable.DataTable)
	{
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

FTradeGoodMasterInfo UInventoryKitFL::GetItemInfoAsTradeGoods(FItemMasterInfo InventoryItem)
{
	FTradeGoodMasterInfo* ItemInfo = nullptr;

	if (IsValid(InventoryItem.ItemDataTable.DataTable))
	{
		ItemInfo = InventoryItem.ItemDataTable.DataTable->FindRow<FTradeGoodMasterInfo>(
			InventoryItem.ItemDataTable.RowName,
			TEXT("AddItem: GetInfo LocInventoryItem"),
			true
			);
	}
	
	return*ItemInfo;
}

FPotionMaterial UInventoryKitFL::GetItemInfoAsPotionMaterial(const FItemMasterInfo& InventoryItem)
{
	FPotionMaterial Result;

	if (!IsValid(InventoryItem.ItemDataTable.DataTable))
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid DataTable in FItemMasterInfo!"));
		return Result;
	}
	
	FPotionMaterial* ItemInfoPtr = InventoryItem.ItemDataTable.DataTable->FindRow<FPotionMaterial>(
		InventoryItem.ItemDataTable.RowName,
		TEXT("GetItemInfoAsPotionMaterial"),
		true
	);

	if (!ItemInfoPtr)
	{
		UE_LOG(LogTemp, Error, TEXT("Row %s not found in DataTable!"), *InventoryItem.ItemDataTable.RowName.ToString());
		return Result;
	}

	return *ItemInfoPtr;
}

TArray<FInventoryItem> UInventoryKitFL::SortItemsByRarity(TArray<FInventoryItem> InventoryItems, bool FromRarest)
{
	if (InventoryItems.Num() != 0)
	{
		InventoryItems.Sort([FromRarest](const FInventoryItem& A, const FInventoryItem& B) {
	const int RarityA = static_cast<int>(UInventoryKitFL::GetInventoryItemInfo(A).BaseItemInfo.ItemRarity);
	const int RarityB = static_cast<int>(UInventoryKitFL::GetInventoryItemInfo(B).BaseItemInfo.ItemRarity);
	return FromRarest ? RarityA > RarityB : RarityA < RarityB;
});
	}
	return InventoryItems;
}

TArray<FInventoryItem> UInventoryKitFL::GetInventoryItems(const UObject* WorldContextObject, EInventoryType TargetInventory)
{
	UInventoryComponent* InventoryComponent = UInventoryKitFL::GetInventoryComponent(WorldContextObject);
	TArray<FInventoryItem> InventoryItems;
	
	if (IsValid(InventoryComponent))
	{
		InventoryItems = InventoryComponent->RequestInventoryArray(TargetInventory);
		return InventoryItems;
	}
	return InventoryItems;
}

UCharacterStatsComponent* UInventoryKitFL::GetPlayerStatsComponent(const UObject* WorldContextObject)
{
	if (!WorldContextObject) 
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid World Context Object!"));
		return nullptr;
	}

	UWorld* World = WorldContextObject->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get World!"));
		return nullptr;
	}
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller not found!"));
		return nullptr;
	}

	APawn* ControlledPawn = PC->GetPawn();
	if (!ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("ControlledPawn is null!"));
		return nullptr;
	}
	
	if (!PC->IsLocalController() || !PC->IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is not local!"));
		return nullptr;
	}
	
	UCharacterStatsComponent* PlayerStatsComponent = ControlledPawn->FindComponentByClass<UCharacterStatsComponent>();
	if (!PlayerStatsComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent not found on Pawn!"));
		return nullptr;
	}

	return PlayerStatsComponent;	
}
