// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "./Enums/PotionProperties/EffectInteractionRule.h"
#include "./DataAssets/EffectDefinition.h"
#include "PotionEffect.generated.h"

/**
* Struct to describe base item info (rarity name, description, Req lvl., icon, etc.)
**/

USTRUCT(BlueprintType)
struct FPotionEffect
{
	GENERATED_BODY()

public:

	FPotionEffect() : IsInstant(false), HasDelayedEffect(false) {}
	
public:

	// Effect strength (for understanding - it is how it affects for example damage caused by effect)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", 
			  meta = (ClampMin = "0.0", UIMin = "0.0", DisplayName = "Potency"))
	float Potency = 1.0f;		// Default - 100%

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", 
			   meta = (ClampMin = "1", ClampMax = "10", DisplayName = "Priority Level"))
	int32 PriorityLevel = 5;

	// Timing of the effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timing", DisplayName = "Is Instant?")
	bool IsInstant;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timing",DisplayName="Duration", meta = (EditCondition = "IsInstant==false"))
	float Duration = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timing", DisplayName = "Has Delayed Effect?")
	bool HasDelayedEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timing",DisplayName="Delay", meta=(EditCondition = "HasDelayedEffect==true"))
	float Delay = 0.0f;

	// Modifiers of effects (for example it contributes "Healing with 200% from healroot to potion")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifiers", DisplayName = "Priority")
	float PriorityWeight = 1.0f;	// Contribution to final effect (default === 100%)
	
	// Flags
	// Effect does damage?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flags", DisplayName = "Is Harmful ?")
	bool IsHarmful = false;

	// For effects which require manual activation (for example - jump boost requires jump button to be pressed, when healing (inst. and regen) will be used instantly)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flags", DisplayName = "Requires Activation?")
	bool RequiresActivation = false;

	// Effect is stackable?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flags", DisplayName = "Is Stackable?")
	bool Stackable = true;

	// Default behaviour for cases when it wasn't described in behaviour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", DisplayName="Interaction Rule")
	EEffectInteractionRule InteractionRule = EEffectInteractionRule::Combine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSoftObjectPtr<UEffectDefinition> EffectDefinition;
};
