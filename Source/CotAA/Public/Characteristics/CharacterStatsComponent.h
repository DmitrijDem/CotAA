// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

// REMARK: I'm tired of generating all C++ files using UE5 tools - "add C++ class" - it takes about 5-10 minutes to compile
// SO, I decided to create next structs here to use them, It is allowed by standard, but less readable in case of
// someone trying to find where they are.

USTRUCT(BlueprintType)
struct FResistanceStats
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Physical;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Water;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Frost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lighting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Psychic;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Poison;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Blood;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Darkness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Light;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Magic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Necrotic;
	
};

USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100 UMETA(DisplayName = "Default Health");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100 UMETA(DisplayName = "Default Health");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina = 100 UMETA(DisplayName = "Default Stamina");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina = 100 UMETA(DisplayName = "Default Health");
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor = 0 UMETA(DisplayName = "Default Armor");

	// Negative resistance === Vulnerability
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FResistanceStats ResistanceModifiers;

	UPROPERTY(EditDefaultsOnly, Category="Stamina")
	float RunDrainRate = -2.f; // Run drain rate

	UPROPERTY(EditDefaultsOnly, Category="Stamina")
	float SprintDrainRate = -6.f; // Sprint drain rate
	
	UPROPERTY(EditDefaultsOnly, Category="Stamina")
	float StaminaRechargeRate = 15.f; // Stamina Recovery rate
};

// (WIP)
// Perks ARE NOT IMPLEMENTED IN PROTOTYPE

UENUM(BlueprintType)
enum class EPerkType : uint8
{
	Select UMETA(DisplayName = "Select"),
	Health UMETA(DisplayName = "Health"),
	Stamina UMETA(DisplayName = "Stamina"),
	CriticalDamage UMETA(DisplayName = "Critical Damage"),
	TotalArmor UMETA(DisplayName = "Total Armor"),
	PhysicalDamage UMETA(DisplayName = "Physical Damage"), // Player has small weapon as "last chance"
	AlchemistKnowledge UMETA(DisplayName = "Alchemist Knowledge"), // Not even sure if it goes here, but I'll leave it as it is
};

USTRUCT(BlueprintType)
struct FPerkInfo
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPerkType PerkType = EPerkType::Select;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture = nullptr;
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COTAA_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatsComponent();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	FCharacterStats DefaultStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCharacterStats CurrentStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPerkInfo> AvailablePerks;
	
	UFUNCTION(BlueprintCallable, Category="Update")
	void UpdateStats();

	UFUNCTION(BlueprintCallable, Category="Update")
	void ResetCurrentStats();

	UFUNCTION(BlueprintCallable, Category="Update")
	void UpdatePerkValue(EPerkType PerkType, int32 NewValue);
	
	UFUNCTION(BlueprintCallable, Category="Update")
	void AddPerk(FPerkInfo PerkInfo);

	// So, previously I was creating structs to return multiple values, but I found out this thing exists in UE
	// all parameters with "&" must be managed by UE workspace as "out" nodes
	// with "const" as "in" nodes
	// If I'm correct
	
	UFUNCTION(BlueprintCallable, Category="Check")
	void IsPerkValid(const EPerkType SearchFor,  bool& Valid, int32& Index, FPerkInfo& PerkInfo);

	// Here must be 2 functions to collect perks info from equipped gear, but, because of lack of time
	// There's no functionality for this (even for equipping gear)

	//UFUNCTION(EditAnywhere, BlueprintCallable, Category="Receive")
	//int32 GetTotalValueFromItems(EBaseGearType GearType)

	//UFUNCTION(EditAnywhere, BlueprintCallable, Category="Receive")
	//void ReceiveEquippedItemPerks()
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Send")
	float GetPerkValue(const EPerkType Perk);

	// "CurrentStats" parameter overrides same one in class
	UFUNCTION(BlueprintCallable, Category="Send")
	void GetCurrentStats(FCharacterStats& pCurrentStats);

	UFUNCTION(BlueprintCallable, Category="Stamina")
	float GetCurrentStamina();
	
	UFUNCTION(BlueprintCallable, Category="Stamina")
	void ChangeCurrentStaminaTo(float Value);
};
