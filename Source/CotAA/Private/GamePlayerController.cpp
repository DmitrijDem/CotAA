// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "InputDataConfig.h"
#include "PlayerCharacter.h"
#include "InteractionSystem/InteractionComponent.h"
#include "Misc/OutputDeviceNull.h"
#include "Enums/UI/InGameMenu.h"
#include "Framework/GameInstanceInterface.h"
#include "FunctionLibraries/InventoryKitFL.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AGamePlayerController::AGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			if (InputMapping)
			{
				Subsystem->AddMappingContext(InputMapping, 0);
			}
		}

		SetMovementState(EMovementState::Walk);
	}
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent && InputComponent)
	{
		// Simple movement/camera input handling
		EnhancedInputComponent->BindAction(InputConfig->IA_Move, ETriggerEvent::Triggered, this, &AGamePlayerController::Move);
		EnhancedInputComponent->BindAction(InputConfig->IA_Look, ETriggerEvent::Triggered, this, &AGamePlayerController::Look);
		EnhancedInputComponent->BindAction(InputConfig->IA_Jump, ETriggerEvent::Triggered, this, &AGamePlayerController::Jump);

		// Interactions handling
		EnhancedInputComponent->BindAction(InputConfig->IA_Interact, ETriggerEvent::Started, this, &AGamePlayerController::OnIA_InteractStarted);
		EnhancedInputComponent->BindAction(InputConfig->IA_Interact, ETriggerEvent::Ongoing, this, &AGamePlayerController::OnIA_InteractOngoing);
		EnhancedInputComponent->BindAction(InputConfig->IA_Interact, ETriggerEvent::Completed, this, &AGamePlayerController::OnIA_InteractOngoing);
		
		// Opening inventory handling
		EnhancedInputComponent->BindAction(InputConfig->IA_OpenInventory, ETriggerEvent::Started, this, &AGamePlayerController::OnIA_OpenInventory);

		// Run/Sprint handling
		EnhancedInputComponent->BindAction(InputConfig->IA_RunSprint, ETriggerEvent::Started, this, &AGamePlayerController::HandleShiftPressed);
		EnhancedInputComponent->BindAction(InputConfig->IA_RunSprint, ETriggerEvent::Completed, this, &AGamePlayerController::HandleShiftReleased);

		// Dodge handling (WIP)
		//EnhancedInputComponent->BindAction(InputConfig->IA_Dodge, ETriggerEvent::Started, this, &AGamePlayerController::HandleDodge);
	}
}

/* ------------------------------ Enhanced Input handler-functions block ------------------------------- */
/* ------------------------------ MoveAction handler-function ------------------------------- */
void AGamePlayerController::Move(const FInputActionValue& Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		const FRotator YawRotation(0, GetControlRotation().Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		const FVector2D InputVector = Value.Get<FVector2D>();
        
		ControlledPawn->AddMovementInput(ForwardDirection, InputVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputVector.X);
	}
}

/* ------------------------------ LookAction handler-function ------------------------------- */
void AGamePlayerController::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	
	AddYawInput(InputVector.X);
	AddPitchInput(InputVector.Y);
}

/* ------------------------------ JumpAction handler-function ------------------------------- */
void AGamePlayerController::Jump()
{
	if (ACharacter* PlayerChar = Cast<ACharacter>(GetPawn()))
	{
		PlayerChar->Jump();
	}
}

void AGamePlayerController::OnIA_InteractStarted()
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		if (PlayerCharacter->GetInteractionComponent())
		{
			PlayerCharacter->GetInteractionComponent()->RequestInteraction();
		}
	}
}

void AGamePlayerController::OnIA_InteractOngoing(const FInputActionInstance& Instance)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		if (PlayerCharacter->GetInteractionComponent())
		{
			float ElapsedSeconds = Instance.GetElapsedTime();
			PlayerCharacter->GetInteractionComponent()->OnInteractionPressOngoing.Broadcast(ElapsedSeconds);
		}
	}
}

void AGamePlayerController::OnIA_InteractCompleted()
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		if (PlayerCharacter->GetInteractionComponent())
		{
			PlayerCharacter->GetInteractionComponent()->OnInteractionPressOngoing.RemoveAll(this);
			if (PlayerCharacter->GetInteractionComponent()->InteractionWidgetRef->FindFunction("SetProgressPercent"))
			{
				FOutputDeviceNull OutputDeviceNull;
				FString Command = FString::Printf(TEXT("SetProgressPercent %f"), 0.0f);
				PlayerCharacter->GetInteractionComponent()->InteractionWidgetRef->CallFunctionByNameWithArguments(*Command, OutputDeviceNull, nullptr, true);
			}
		}
	}
}


void AGamePlayerController::OnIA_OpenInventory()
{
	IGameInstanceInterface::Execute_ToggleInGameMenu(GetGameInstance(), EInGameMenu::Inventory);
}

void AGamePlayerController::SetMovementState(EMovementState NewState)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn()))
	{
		CurrentMovementState = NewState;
		float NewSpeed = WalkSpeed;
        
		switch (NewState)
		{
		case EMovementState::Run: NewSpeed = RunSpeed; break;
		case EMovementState::Sprint: NewSpeed = SprintSpeed; break;
		}
        
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
	}
}

void AGamePlayerController::HandleShiftPressed(const FInputActionValue& Value)
{
	// Extra check, that we CAN run or sprint
	if (UInventoryKitFL::GetPlayerStatsComponent(GetWorld())->GetCurrentStamina() <= 0) return;

	float CurrentTime = GetWorld()->GetTimeSeconds();
	
	if (bWaitingForSecondTap && (CurrentTime - LastShiftPressTime) < DoubleTapTime)
	{
		bWaitingForSecondTap = false;
		Sprint();
		return;
	}
	
	bIsShiftHold = true;
	bWaitingForSecondTap = true;
	LastShiftPressTime = CurrentTime;
	
	GetWorldTimerManager().SetTimer(SprintTapTimer, this, &AGamePlayerController::CheckForHold, DoubleTapTime, false);
}

void AGamePlayerController::HandleShiftReleased(const FInputActionValue& Value)
{
	bIsShiftHold = false;
    
	if (CurrentMovementState == EMovementState::Sprint)
	{
		StopSprinting();
	}
	else if (CurrentMovementState == EMovementState::Run)
	{
		StopRunning();
	}
}

void AGamePlayerController::CheckForHold()
{
	 if (bIsShiftHold && bWaitingForSecondTap && UInventoryKitFL::GetPlayerStatsComponent(GetWorld())->GetCurrentStamina() > 0)
    {
        Run();
    }
    bWaitingForSecondTap = false;
}

void AGamePlayerController::Run()
{
	if (CurrentMovementState != EMovementState::Run)
	{
		SetMovementState(EMovementState::Run);
		ManageStaminaTimers(true);
	}
}

void AGamePlayerController::StopRunning()
{
	if (CurrentMovementState == EMovementState::Run)
	{
		SetMovementState(EMovementState::Walk);
		ManageStaminaTimers(false);
	}
}

void AGamePlayerController::Sprint()
{
	if (CurrentMovementState != EMovementState::Sprint)
	{
		SetMovementState(EMovementState::Sprint);
		ManageStaminaTimers(true);
	}
}

void AGamePlayerController::StopSprinting()
{
	if (CurrentMovementState == EMovementState::Sprint)
	{
		SetMovementState(EMovementState::Walk);
		ManageStaminaTimers(false);
	}
}

void AGamePlayerController::ManageStaminaTimers(bool bDrain)
{
	if (bDrain)
	{
		GetWorldTimerManager().ClearTimer(StaminaRechargeHandle);
		if (!GetWorldTimerManager().IsTimerActive(StaminaDrainHandle))
		{
			GetWorldTimerManager().SetTimer(StaminaDrainHandle, this, &AGamePlayerController::DrainStamina, StaminaDrainFrequency, true);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(StaminaDrainHandle);
		if (!GetWorldTimerManager().IsTimerActive(StaminaRechargeHandle))
		{
			GetWorldTimerManager().SetTimer(StaminaRechargeHandle, this, &AGamePlayerController::RechargeStamina, StaminaRechargeFrequency, true);
		}
	}
}

void AGamePlayerController::DrainStamina()
{
	// Actually, it is bad to do this if I'm right, but I have no time to do it in better way (maybe functions in component etc.)
	// So, I'll do it straight way by changing values here (do not do this in normal projects, if you will change component values
	// in multiple places - it will be hard to find where - much better way - use functions like Component->ChangeStamina(float value))
	UPlayerStatsComponent* StatsComponent = UInventoryKitFL::GetPlayerStatsComponent(GetWorld());
	if (!StatsComponent) return;
	float CurrentStamina = StatsComponent->GetCurrentStamina();
	
	if (CurrentStamina > 0)
	{
		float DrainRate = 0.f;
		switch (CurrentMovementState)
		{
			case EMovementState::Run: DrainRate = StatsComponent->CurrentStats.RunDrainRate;  break;
			case EMovementState::Sprint: DrainRate = StatsComponent->CurrentStats.SprintDrainRate; break;
		}
		
		StatsComponent->ChangeCurrentStaminaTo(CurrentStamina = FMath::Max(CurrentStamina + DrainRate, 0));
	}
	else
	{
		switch (CurrentMovementState)
		{
		case EMovementState::Run: StopRunning(); break;
		case EMovementState::Sprint: StopSprinting(); break;
		}
	}

	// Stop draining stamina when player doesn't trying to run or sprint
	if (CurrentStamina <= 0 && CurrentMovementState != EMovementState::Run && CurrentMovementState != EMovementState::Sprint)
	{
		GetWorldTimerManager().ClearTimer(StaminaDrainHandle);
	}

	// calculate percentage (to use in UI)
	float StaminaPercent = CurrentStamina / StatsComponent->CurrentStats.MaxStamina;
	
}

void AGamePlayerController::RechargeStamina()
{
	UPlayerStatsComponent* StatsComponent = UInventoryKitFL::GetPlayerStatsComponent(GetWorld());
	if (!StatsComponent) return;
	float CurrentStamina = StatsComponent->GetCurrentStamina();

	if ((CurrentMovementState != EMovementState::Run && CurrentMovementState != EMovementState::Sprint))
	if (CurrentStamina < StatsComponent->CurrentStats.MaxStamina)
	{
		CurrentStamina = FMath::Min(CurrentStamina + StatsComponent->CurrentStats.StaminaRechargeRate, StatsComponent->CurrentStats.MaxStamina);
		StatsComponent->ChangeCurrentStaminaTo(CurrentStamina);
	}

	// When player's stamina is full - stop recharging
	if (CurrentStamina >= StatsComponent->CurrentStats.MaxStamina)
	{
		GetWorldTimerManager().ClearTimer(StaminaRechargeHandle);
	}

	
	// calculate percentage (to use in UI)
	float StaminaPercent = CurrentStamina / StatsComponent->CurrentStats.MaxStamina;
	
}