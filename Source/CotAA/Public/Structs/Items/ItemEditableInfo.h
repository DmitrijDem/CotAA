// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




#include "CoreMinimal.h"
#include "ItemEditableInfo.generated.h"
/**
* Struct to describe Inventory Item
**/

USTRUCT(BlueprintType)
struct FItemEditableInfo
{
	GENERATED_BODY()

public:

	FItemEditableInfo() {};
	FItemEditableInfo(int pAmount) : Amount(pAmount) {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Is Selected Gear?")
	bool bIsSelected = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Amount")
	int Amount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName = "Current Item Level")
	int CurrentItemLevel = 1;
};
