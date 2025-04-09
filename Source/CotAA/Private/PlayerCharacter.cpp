// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
/* ------------------------------ Enhanced Input Libraries------------------------------- */
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
/* ------------------------------ Components Libraries------------------------------- */
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
/* ------------------------------ Custom Libraries------------------------------- */
#include "InteractionSystem/InteractionComponent.h"
#include "InteractionSystem/InventoryComponent.h"
#include "Misc/OutputDeviceNull.h"
/* ------------------------------ Constructor ------------------------------- */
APlayerCharacter::APlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	// Setting up spring arm and camera 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SocketOffset = FVector(0.0f, 55.0f, 60.0f);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = false;

	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.0f;

	SpringArm->CameraLagMaxDistance = 100.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// Setting capsule component for interactions

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

	// Interaction Component
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");

	// Inventory Component

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");
}

/* ------------------------------ BeginPlay ------------------------------- */
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

/* ------------------------------ Tick ------------------------------- */
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/* ------------------------------ Enhanced Input Setup (4) ------------------------------- */
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (InputConfig)
		{
			Input->BindAction(InputConfig->IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
			Input->BindAction(InputConfig->IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
			Input->BindAction(InputConfig->IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
			if (InputConfig->IA_Interact && InteractionComponent)
			{
				Input->BindAction(InputConfig->IA_Interact, ETriggerEvent::Started, this, &APlayerCharacter::OnIA_InteractStarted);
				Input->BindAction(InputConfig->IA_Interact, ETriggerEvent::Ongoing, this, &APlayerCharacter::OnIA_InteractOngoing);
				Input->BindAction(InputConfig->IA_Interact, ETriggerEvent::Completed, this, &APlayerCharacter::OnIA_InteractOngoing);
			}
		}
	}
}

/* ------------------------------ Enhanced Input handler-functions block ------------------------------- */
/* ------------------------------ MoveAction handler-function ------------------------------- */
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// Get Forward Direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement input
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);
	}
}

/* ------------------------------ LookAction handler-function ------------------------------- */
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	
	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

/* ------------------------------ JumpAction handler-function ------------------------------- */
void APlayerCharacter::Jump()
{
	ACharacter::Jump();
}

void APlayerCharacter::OnIA_InteractStarted()
{
	InteractionComponent->RequestInteraction();
}

void APlayerCharacter::OnIA_InteractOngoing(const FInputActionInstance& Instance)
{
	float ElapsedSeconds = Instance.GetElapsedTime();
	InteractionComponent->OnInteractionPressOngoing.Broadcast(ElapsedSeconds);
}

void APlayerCharacter::OnIA_InteractCompleted()
{
	InteractionComponent->OnInteractionPressOngoing.RemoveAll(this);
	if (InteractionComponent->InteractionWidgetRef->FindFunction("SetProgressPercent"))
	{
		FOutputDeviceNull OutputDeviceNull;
		FString Command = FString::Printf(TEXT("SetProgressPercent %f"), 0.0f);
		InteractionComponent->InteractionWidgetRef->CallFunctionByNameWithArguments(*Command, OutputDeviceNull, nullptr, true);
	}
}

UInventoryComponent* APlayerCharacter::GetInventoryComponent() const
{
	if (InventoryComponent)
	{
		return Cast<UInventoryComponent>(GetComponentByClass(UInventoryComponent::StaticClass()));
	}

	return nullptr;
}
