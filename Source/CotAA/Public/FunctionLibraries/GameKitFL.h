// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameKitFL.generated.h"

/**
 * 
 */

UCLASS()
class COTAA_API UGameKitFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintPure)
	static float CalculateAnimationCurrentTime(UUserWidget* SelfReference, UWidgetAnimation* InAnimation);
};
