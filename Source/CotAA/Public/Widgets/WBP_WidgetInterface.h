// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WBP_WidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWBP_WidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**---------------------------- Interface Definition ----------------------------- **/

/**
 * Interface used in widget blueprints
 **/
class COTAA_API IWBP_WidgetInterface
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SimulateClick();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ScrollScrollBox(bool Up, float SpeedMultiplier);
	
};
