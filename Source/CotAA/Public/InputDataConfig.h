// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "InputDataConfig.generated.h"

/**
 *  Data asset to put inside all Input Actions and attach it to player
 *  Better for organization, but sometimes, on failed build - you might need to recreate file inside editor
 */
UCLASS()
class COTAA_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Movement")
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Movement")
	class UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Movement")
	class UInputAction* IA_Jump;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Interaction")
	class UInputAction* IA_Interact;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Inventory")
	class UInputAction* IA_OpenInventory;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Movement")
	class UInputAction* IA_RunSprint;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput|Battle")
	class UInputAction* IA_Dodge;
};
