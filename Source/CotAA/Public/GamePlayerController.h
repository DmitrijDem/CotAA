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

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Walk,
	Run,
	Sprint
};

UCLASS()
class COTAADEV_API AGamePlayerController : public APlayerController, public IPlayerControllerInterface
{
	GENERATED_BODY()

private:
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
	
	UFUNCTION(BlueprintCallable)
	void SetMovementState(EMovementState NewState);

	// Shift is default button to run/sprint
	UFUNCTION(BlueprintCallable)
	void HandleShiftPressed(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable)
	void HandleShiftReleased(const FInputActionValue& Value);
	
	EMovementState CurrentMovementState = EMovementState::Walk;

	float WalkSpeed = 400.f;
	float RunSpeed = 600.f;
	float SprintSpeed = 1000.f;

	FTimerHandle SprintTapTimer;
	int32 ShiftPressCount = 0;
	bool bIsShiftHold = false;
	bool bWaitingForSecondTap = false;
	float LastShiftPressTime = 0.f;
	const float DoubleTapTime = 0.3f;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	float StaminaDrainFrequency = .3f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float StaminaRechargeFrequency = .3f;

	FTimerHandle StaminaDrainHandle;
	FTimerHandle StaminaRechargeHandle;

public:

	// Run handler functions
	void Run();
	void StopRunning();

	// Sprint handler functins
	void Sprint();
	void StopSprinting();

	// Timer-manager-function
	void ManageStaminaTimers(bool bDrain);
	
	// Timer handlers to find if
	// 1- player pressed 1 or 2 times LShift (default)
	// 2- DrainStamina (logic to find which statement he is now - inside)
	// 3- RechargeStamina (logic to find player is not in drain stamina state - inside)
	
	void CheckForHold();
	void DrainStamina();
	void RechargeStamina();

	
	
	/**------------------------------ Enhanced Input Block------------------------------- **/

public:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputDataConfig* InputConfig;
	
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent;
};
