// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPotionEffectType : uint8
{
    // ========================
    // Core Effects
    // ========================
    None                UMETA(DisplayName = "None"),

    // ========================
    // Primary Effects 
    // ========================
    // Healing & Stamina
    Healing             UMETA(DisplayName = "Healing"),
    Regeneration        UMETA(DisplayName = "Regeneration"),
    StaminaRestore      UMETA(DisplayName = "Stamina Restore"),
    StaminaRegeneration UMETA(DisplayName = "Stamina Regeneration"),

    // Damage Types
    FireDamage          UMETA(DisplayName = "Fire Damage"),
   FrostDamage         UMETA(DisplayName = "Frost Damage"),
   PoisonDamage        UMETA(DisplayName = "Poison Damage"),
   LightningDamage     UMETA(DisplayName = "Lightning Damage"),
   BloodDamage         UMETA(DisplayName = "Blood Damage"),
   PsychicDamage       UMETA(DisplayName = "Psychic Damage"),
   NecroticDamage      UMETA(DisplayName = "Necrotic Damage"),
   PhysicalDamage      UMETA(DisplayName = "Physical Damage"),
   AcidDamage          UMETA(DisplayName = "Acid Damage"), 
   LightDamage          UMETA(DisplayName = "Light Damage"),
   DarkDamage          UMETA(DisplayName = "Dark Damage"),
   ChaosDamage         UMETA(DisplayName = "Chaos Damage"),

	Bleeding            UMETA(DisplayName = "Bleeding Damage"),

    // ========================
    // Defense Modifiers 
    // ========================
    // Unified Defense System (Power defines strength and resistance\vulnerability)
	PhysicalResistance  UMETA(DisplayName = "Physical Resistance"),
	FireResistance      UMETA(DisplayName = "Fire Resistance"),
	FrostResistance     UMETA(DisplayName = "Frost Resistance"),
	PoisonResistance    UMETA(DisplayName = "Poison Resistance"),
	LightningResistance UMETA(DisplayName = "Lightning Resistance"),
	BloodResistance     UMETA(DisplayName = "Blood Resistance"),
	PsychicResistance   UMETA(DisplayName = "Psychic Resistance"),
	NecroticResistance  UMETA(DisplayName = "Necrotic Resistance"),
	AcidResistance      UMETA(DisplayName = "Acid Resistance"),
	LightResistance      UMETA(DisplayName = "Light Resistance"),
	DarkResistance      UMETA(DisplayName = "Dark Resistance"),
	ChaosResistance     UMETA(DisplayName = "Chaos Resistance"),

	UniversalResistance UMETA(DisplayName = "Universal Resistance"),

    // ========================
    // Special Conditions 
    // ========================
    Corrosion           UMETA(DisplayName = "Corrosion"),    // Armor reducing
    Curse               UMETA(DisplayName = "Curse"),        // Increasing incoming damage
	Invisibility         UMETA(DisplayName = "Invisibility"),
    // ========================
    // Hidden Application Flags 
    // ========================
    // Pre-conditions to use potion without penalties
    RequiresHeatResist  UMETA(DisplayName = "Requires Heat Resistance"), // requires Fire Resistance
    RequiresColdVulnerable UMETA(DisplayName = "Requires Cold Vulnerability"), // Requires Frost Resistance
    RequiresBleeding UMETA(DisplayName = "Requires Bleeding"),                  // Requires player to bleed (lose hp/sec)
    RequiresMoonPhase UMETA(DisplayName = "Requires Moon Phase"),               // Requires special moon phase (WIP)
};