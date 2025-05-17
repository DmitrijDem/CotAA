// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStats/PlayerStatsComponent.h"

#include "Layers/LayersSubsystem.h"

// Sets default values for this component's properties
UPlayerStatsComponent::UPlayerStatsComponent()
{
	// Nothing
}

void UPlayerStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	ResetCurrentStats();
}

void UPlayerStatsComponent::UpdateStats()
{
	ResetCurrentStats();
	// ReceiveEquippedItemPerks()

	// Get DefaultHealth + same default * health perk modifiers from gear and divide by 100
	CurrentStats.Health = CurrentStats.Health +
		FMath::TruncateToHalfIfClose((CurrentStats.Health * GetPerkValue(EPerkType::Health)) / 100.0f);

	CurrentStats.Stamina = CurrentStats.Stamina +
		FMath::TruncateToHalfIfClose((CurrentStats.Stamina * GetPerkValue(EPerkType::Stamina)) / 100.0f);
	// GetTotalValuesFromItems(EBaseGear::Weapon)
	// Do smth with player Physical damage etc.

	// (WIP) - I might add armor which player can "wear" (I don't have proper 3D-model of the main character)
	// int32 ArmorSum = GetTotalValuesFromItems(EBaseGear::Armor) + CurrentStats.Armor
	// CurrentStats.Armor = FMath::TruncateToHalfIfClose(ArmorSum * GetPerkValue(EPerkType::TotalArmor / 100.0f)) + ArmorSum;

	// Add other perks here (for example, potion effects multiplied when player drinks it, larger area for bombs explosion etc.)
}

void UPlayerStatsComponent::ResetCurrentStats()
{
	CurrentStats = DefaultStats;
	AvailablePerks.Empty();
}

void UPlayerStatsComponent::UpdatePerkValue(EPerkType PerkType, int32 NewValue)
{
	for (auto Element : AvailablePerks)
	{
		if (Element.PerkType == PerkType)
		{
			Element.Value = NewValue;
		}
	}
}

void UPlayerStatsComponent::AddPerk(FPerkInfo PerkInfo)
{
	bool bValid = false;
	int32 FoundIndex = -1;
	FPerkInfo ExistingPerkInfo;
	IsPerkValid(PerkInfo.PerkType, bValid, FoundIndex, ExistingPerkInfo);
	if(bValid)
	{
		if (ExistingPerkInfo.PerkType == PerkInfo.PerkType)
		{
			UpdatePerkValue(PerkInfo.PerkType, AvailablePerks[FoundIndex].Value + PerkInfo.Value);
		}
		else
		{
			AvailablePerks.Add(PerkInfo);
		}
	}
	else
	{
		AvailablePerks.Add(PerkInfo);
	}
}

void UPlayerStatsComponent::IsPerkValid(const EPerkType SearchFor, bool& Valid, int32& Index, FPerkInfo& PerkInfo)
{
	bool LocValid = false;
	int32 LocIndex = -1;
	FPerkInfo LocPerkInfo{};
	
	if (AvailablePerks.Num() != 0)
	{
		// Used for (int i...) because I need index
		for (int i = 0; i < AvailablePerks.Num(); i++)
		{
			if (AvailablePerks[i].PerkType == SearchFor)
			{
				LocPerkInfo = AvailablePerks[i];
				LocValid = true;
				LocIndex = i;
				break;
			}
		}
	}

	Valid = LocValid;
	Index = LocIndex;
	PerkInfo = LocPerkInfo;
}

float UPlayerStatsComponent::GetPerkValue(const EPerkType Perk)
{
	int32 LocPerkValue = 0;
	for (auto PerkInfo: AvailablePerks)
	{
		if (PerkInfo.PerkType == Perk)
		{
			LocPerkValue = PerkInfo.Value;
			break;
		}
	}
	return LocPerkValue;
}

void UPlayerStatsComponent::GetCurrentStats(FPlayerStats& pCurrentStats)
{
	pCurrentStats = CurrentStats;
}

float UPlayerStatsComponent::GetCurrentStamina()
{	
	return CurrentStats.Stamina;
}

void UPlayerStatsComponent::ChangeCurrentStaminaTo(float Value)
{
	CurrentStats.Stamina = Value;
}

