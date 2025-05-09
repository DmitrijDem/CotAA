// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType, meta=(BitFlags))
enum class EPotionEffectType : uint8
{
    // ========================
    // Default
    // ========================
    None          UMETA(DisplayName = "None"),
	
	// ========================
	// Positive Effects 
	// ========================
	Healing             UMETA(DisplayName = "Healing"),
	Regeneration        UMETA(DisplayName = "Regeneration"),
	StaminaRestore      UMETA(DisplayName = "Stamina Restore"),
	StaminaRegeneration UMETA(DisplayName = "Stamina Regeneration"),

	// Resistances
	PhysicalResistance  UMETA(DisplayName = "Physical Resistance"),  // Might be separated ("Skyrim" - oak and stone skin)
	FireResistance      UMETA(DisplayName = "Fire Resistance"),
	FrostResistance     UMETA(DisplayName = "Frost Resistance"),
	LightningResistance UMETA(DisplayName = "Lightning Resistance"),
	PsychicResistance   UMETA(DisplayName = "Psychic Resistance"), 
	PoisonResistance    UMETA(DisplayName = "Poison Resistance"),
	BloodResistance     UMETA(DisplayName = "Blood Resistance"),
	DarkResistance      UMETA(DisplayName = "Dark Resistance"),
	LightResistance     UMETA(DisplayName = "Light Resistance"),
	MagicResistance     UMETA(DisplayName = "Magic Resistance"),
	NecroticResistance  UMETA(DisplayName = "Necrotic Resistance"),
	WaterResistance     UMETA(DisplayName = "Water Resistance"),
	
	// ========================
	// Negative Effects 
	// ========================
	Flame				UMETA(DisplayName = "Flame"),
	Frost				UMETA(DisplayName = "Frost"),
	Poison				UMETA(DisplayName = "Poison"),
	Lightning			UMETA(DisplayName = "Lightning"),
	BloodDamage			UMETA(DisplayName = "Blood"),
	PsychicDamage       UMETA(DisplayName = "Madness"),
	SoulDrain           UMETA(DisplayName = "Soul Drain"),
	Corrosion           UMETA(DisplayName = "Corrosion"),		// Reduce armor (not health? maybe)
	Curse               UMETA(DisplayName = "Curse"),			// If I'm doing system correctly - this + any damageEffect === Vulnerability to this damage type

	// Vulnerabilities
	PhysicalVulnerability  UMETA(DisplayName = "Physical Vulnerability"),  // Might be separated ("Skyrim" - oak and stone skin)
	FireVulnerability      UMETA(DisplayName = "Fire Vulnerability"),
	FrostVulnerability     UMETA(DisplayName = "Frost Vulnerability"),
	LightningVulnerability UMETA(DisplayName = "Lightning Vulnerability"),
	PsychicVulnerability   UMETA(DisplayName = "Psychic Vulnerability"), 
	PoisonVulnerability    UMETA(DisplayName = "Poison Vulnerability"),
	BloodVulnerability     UMETA(DisplayName = "Blood Vulnerability"),
	DarkVulnerability     UMETA(DisplayName = "Dark Vulnerability"),
	LightVulnerability     UMETA(DisplayName = "Light Vulnerability"),
	MagicVulnerability     UMETA(DisplayName = "Magic Vulnerability"),
	NecroticVulnerability  UMETA(DisplayName = "Necrotic Vulnerability"),
	WaterVulnerability    UMETA(DisplayName = "Water Vulnerability"),

	// ========================
	// Hidden Effects (Requirement/System)
	// ========================
	RequiresCatalyst    UMETA(DisplayName = "Requires Catalyst", Hidden),      // Catalysator === other effect or specialized material
	RequiresMoonPhase   UMETA(DisplayName = "Requires Moon Phase", Hidden),    //
	RequiresBlood UMETA(DisplayName = "Requires Blood ", Hidden),			   // One of the materials is blood
	VolatileCompound    UMETA(DisplayName = "Volatile Compound", Hidden)       // Might change something in effects (their layer, to other random effect etc.)
};

ENUM_CLASS_FLAGS(EPotionEffectType);