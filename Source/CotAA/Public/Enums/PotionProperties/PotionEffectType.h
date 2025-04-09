// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPotionEffectType : uint8
{
    // Requirement Effects
    Heating          UMETA(DisplayName = "Heating", Category = "Requirement Effects"),
    Cooling          UMETA(DisplayName = "Cooling", Category = "Requirement Effects"),
    Stabilizing      UMETA(DisplayName = "Stabilizing", Category = "Requirement Effects"),

    // Healing Effects
    Healing          UMETA(DisplayName = "Healing", Category = "Healing Effects"),
    Regeneration     UMETA(DisplayName = "Regeneration", Category = "Healing Effects"),
    StaminaBoost     UMETA(DisplayName = "Stamina Boost", Category = "Healing Effects"),

    // Beneficial Effects
    Strength         UMETA(DisplayName = "Strength", Category = "Beneficial Effects"),
    Speed            UMETA(DisplayName = "Speed", Category = "Beneficial Effects"),
    Invisibility     UMETA(DisplayName = "Invisibility", Category = "Beneficial Effects"),
    NightVision      UMETA(DisplayName = "Night Vision", Category = "Beneficial Effects"),
    PlantVision      UMETA(DisplayName = "Plant Vision", Category = "Beneficial Effects"),
    LootVision       UMETA(DisplayName = "Loot Vision", Category = "Beneficial Effects"),
    EnemyVision      UMETA(DisplayName = "Enemy Vision", Category = "Beneficial Effects"),

    // Resistances
    FireResistance    UMETA(DisplayName = "Fire Resistance", Category = "Resistances"),
    FrostResistance   UMETA(DisplayName = "Frost Resistance", Category = "Resistances"),
    ShockResistance   UMETA(DisplayName = "Shock Resistance", Category = "Resistances"),
    PoisonResistance  UMETA(DisplayName = "Poison Resistance", Category = "Resistances"),
    LightResistance   UMETA(DisplayName = "Light Resistance", Category = "Resistances"),
    GloomResistance   UMETA(DisplayName = "Gloom Resistance", Category = "Resistances"),

    // Harmful Effects
    Poison           UMETA(DisplayName = "Poison", Category = "Harmful Effects"),
    Burning          UMETA(DisplayName = "Burning", Category = "Harmful Effects"),
    Freezing         UMETA(DisplayName = "Freezing", Category = "Harmful Effects"),
    Electrocution    UMETA(DisplayName = "Electrocution", Category = "Harmful Effects"),
    Corrosion        UMETA(DisplayName = "Corrosion", Category = "Harmful Effects"),
    Bleeding         UMETA(DisplayName = "Bleeding", Category = "Harmful Effects"),
    Drunk            UMETA(DisplayName = "Drunk", Category = "Harmful Effects"),
    Confusion        UMETA(DisplayName = "Confusion", Category = "Harmful Effects"),
    Fear             UMETA(DisplayName = "Fear", Category = "Harmful Effects"),

    // Elemental Damage
    FireDamage       UMETA(DisplayName = "Fire Damage", Category = "Elemental Damage"),
    FrostDamage      UMETA(DisplayName = "Frost Damage", Category = "Elemental Damage"),
    ElectricDamage   UMETA(DisplayName = "Electric Damage", Category = "Elemental Damage"),
    PoisonDamage     UMETA(DisplayName = "Poison Damage", Category = "Elemental Damage"),
    NecroticDamage   UMETA(DisplayName = "Necrotic Damage", Category = "Elemental Damage"),

    // Physical Transformations
    DensityIncrease  UMETA(DisplayName = "Density Increase", Category = "Physical Transformations"),
    DensityDecrease  UMETA(DisplayName = "Density Decrease", Category = "Physical Transformations"),
    ViscosityChange  UMETA(DisplayName = "Viscosity Change", Category = "Physical Transformations"),
    PhaseShift       UMETA(DisplayName = "Phase Shift", Category = "Physical Transformations"),

    // Time Manipulation
    TimeDilation     UMETA(DisplayName = "Time Dilation", Category = "Time Manipulation"),
    TimeAcceleration UMETA(DisplayName = "Time Acceleration", Category = "Time Manipulation"),
    Precognition     UMETA(DisplayName = "Precognition", Category = "Time Manipulation"),

    // Special Effects
    Chaos            UMETA(DisplayName = "Chaos", Category = "Special Effects"),
    LifeSteal        UMETA(DisplayName = "Life Steal", Category = "Special Effects"),
    Resurrection     UMETA(DisplayName = "Resurrection", Category = "Special Effects"),
    Polymorph        UMETA(DisplayName = "Polymorph", Category = "Special Effects"),
    Teleportation    UMETA(DisplayName = "Teleportation", Category = "Special Effects"),
    GravityShift     UMETA(DisplayName = "Gravity Shift", Category = "Special Effects"),

    // Post-Effects
    Hangover         UMETA(DisplayName = "Hangover", Category = "Post-Effects"),
    Withdrawal       UMETA(DisplayName = "Withdrawal", Category = "Post-Effects"),
    ImmunityFatigue  UMETA(DisplayName = "Immunity Fatigue", Category = "Post-Effects"),
    RealityLag       UMETA(DisplayName = "Reality Lag", Category = "Post-Effects"),

    // World Interaction
    PlantGrowth      UMETA(DisplayName = "Plant Growth", Category = "World Interaction"),
    CrystalGrowth    UMETA(DisplayName = "Crystal Growth", Category = "World Interaction"),
    WaterPurification UMETA(DisplayName = "Water Purification", Category = "World Interaction"),

    // Default
    Select           UMETA(DisplayName = "Select", Category = "Default")
};