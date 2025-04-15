// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructUtils/UserDefinedStruct.h"
#include "TradeGoodMasterInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct COTAADEV_API FTradeGoodMasterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:

	FTradeGoodMasterInfo()
		: Amount(1)
		, ValueAsCoin(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Amount")
	int Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value As Coin")
	int ValueAsCoin;
};
