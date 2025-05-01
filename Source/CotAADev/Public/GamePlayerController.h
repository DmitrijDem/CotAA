// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InteractionSystem/PlayerControllerInterface.h"
#include "GamePlayerController.generated.h"


// Forward Declaration
class UInputDataConfig;
class UInputAction;
class UEnhancedInputComponent;
class UInteractionComponent;

/**
 * 
 */

UCLASS()
class COTAADEV_API AGamePlayerController : public APlayerController, public IPlayerControllerInterface
{
	GENERATED_BODY()

public:
	AGamePlayerController();

	/**----------- IA Handle functions block ----------- **/
	// MoveAction handler
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	// LookAction handler
	UFUNCTION()
	void Look(const FInputActionValue& Value);

	// InteractAction handler
	void Jump();
		
	// handles InteractionComponent behavior on started action
	void OnIA_InteractStarted();

	// handles InteractionComponent on ongoing action
	void OnIA_InteractOngoing(const FInputActionInstance& Instance);

	// handles InteractionComponent behavior on completed action
	void OnIA_InteractCompleted();

	// Handles Inventory opening
	UFUNCTION(BlueprintCallable)
	void OnIA_OpenInventory();


	/**------------------------------ Enhanced Input Block------------------------------- **/

	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputDataConfig* InputConfig;
	
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;
	
};
