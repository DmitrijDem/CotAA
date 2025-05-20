// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputDataConfig.h"
#include "Characteristics/CharacterStatsComponent.h"
#include "PlayerCharacter.generated.h"

/**------------------------------ Forward declaration block begin------------------------------- **/
// This block serves as "I know, there WILL BE some class which will be used in blueprints, but they are not #included yet"
class UInventoryComponent;
/**------------------------------ Forward declaration block end------------------------------- **/
class UInteractionComponent;

UCLASS()
class COTAADEV_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/**------------------------------ Components block------------------------------- **/

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;
		
	/**------------------------------ Constructor ------------------------------- **/
public:
	APlayerCharacter();

	// setup functions
	void ConfigureCamera();
	
	/**------------------------------ BeginPlay ------------------------------- **/
protected:
	virtual void BeginPlay() override;
	/**------------------------------ Tick event ------------------------------- **/
public:
	virtual void Tick(float DeltaTime) override;

private:
	/**------------------------------ Custom Components block ------------------------------- **/
	/** ----------- Interaction component ----------- **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInteractionComponent* InteractionComponent;
	
	/** ----------- Inventory component ----------- **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	/** ----------- PlayerStats component  ----------- **/
	// handles HP, stamina, resistances, perks etc.
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCharacterStatsComponent* PlayerStatsComponent;
	
public:
	UInventoryComponent* GetInventoryComponent() const;

	UInteractionComponent* GetInteractionComponent() const;
	
};
