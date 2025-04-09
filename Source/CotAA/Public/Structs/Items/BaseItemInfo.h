// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/ItemProperties/ItemRarity.h"
#include "BaseItemInfo.generated.h"

/**
 * Struct to describe RarityChance of the item
 */
USTRUCT(BlueprintType)
struct COTAA_API FBaseItemInfo
{
	GENERATED_BODY()

	public:

	FBaseItemInfo()
		: ItemRarity(EItemRarity::Select)
		, Name(FText::GetEmpty())
		, Description(FText::GetEmpty())
		, RequiredLevel(0)
		, Icon(nullptr)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rarity")
	EItemRarity ItemRarity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Required Level")
	int RequiredLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Icon")
	TObjectPtr<UTexture2D> Icon = nullptr;
};
