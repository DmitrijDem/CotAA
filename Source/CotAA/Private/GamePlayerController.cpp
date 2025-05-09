// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "EnhancedInputSubsystems.h"
#include "InputDataConfig.h"
#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "InteractionSystem/InteractionComponent.h"
#include "Misc/OutputDeviceNull.h"
#include "Enums/UI/InGameMenu.h"
#include "Framework/GameInstanceInterface.h"

AGamePlayerController::AGamePlayerController()
{
	
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
	}
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent && InputComponent)
	{
		EnhancedInputComponent->BindAction(InputConfig->IA_Move, ETriggerEvent::Triggered, this, &AGamePlayerController::Move);
		EnhancedInputComponent->BindAction(InputConfig->IA_Look, ETriggerEvent::Triggered, this, &AGamePlayerController::Look);
		EnhancedInputComponent->BindAction(InputConfig->IA_Jump, ETriggerEvent::Triggered, this, &AGamePlayerController::Jump);
		if (InputConfig->IA_Interact)
		{
			EnhancedInputComponent->BindAction(InputConfig->IA_Interact, ETriggerEvent::Started, this, &AGamePlayerController::OnIA_InteractStarted);
			EnhancedInputComponent->BindAction(InputConfig->IA_Interact, ETriggerEvent::Ongoing, this, &AGamePlayerController::OnIA_InteractOngoing);
			EnhancedInputComponent->BindAction(InputConfig->IA_Interact, ETriggerEvent::Completed, this, &AGamePlayerController::OnIA_InteractOngoing);
		}
		EnhancedInputComponent->BindAction(InputConfig->IA_OpenInventory, ETriggerEvent::Started, this, &AGamePlayerController::OnIA_OpenInventory);
	}
}

/* ------------------------------ Enhanced Input handler-functions block ------------------------------- */
/* ------------------------------ MoveAction handler-function ------------------------------- */
void AGamePlayerController::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn())
	{
		if (IsValid(ControlledPawn))
		{
			// Get Forward Direction
			const FRotator Rotation = GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// Add movement input
			ControlledPawn->AddMovementInput(ForwardDirection, InputVector.Y);
			ControlledPawn->AddMovementInput(RightDirection, InputVector.X);
		}
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