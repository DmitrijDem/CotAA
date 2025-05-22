// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *  Enumerator to describe item rarity
 */
UENUM(BlueprintType)
enum class  EItemType : uint8
{
	Select UMETA(DisplayName = "Select"),
	Gear UMETA(DisplayName = "Gear"),
	QuestItem UMETA(DisplayName = "Quest Item"),
	Document UMETA(DisplayName = "Document"),
	TradeGood UMETA(DisplayName = "Trade Good"),
	PotionMaterial UMETA(DisplayName = "Potion Material"),
};
