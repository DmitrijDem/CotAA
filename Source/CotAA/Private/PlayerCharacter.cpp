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
#include "Misc/OutputDeviceNull.h"
/* ------------------------------ Constructor (1) ------------------------------- */
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
}

/* ------------------------------ BeginPlay (2) ------------------------------- */
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

/* ------------------------------ Tick (3) ------------------------------- */
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
		GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Red, "Player Character Input set up");
		Input->BindAction(IA_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		Input->BindAction(IA_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		Input->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		if (IA_Interact)
		{
			Input->BindAction(IA_Interact, ETriggerEvent::Started, this, &APlayerCharacter::OnIA_InteractStarted);
			Input->BindAction(IA_Interact, ETriggerEvent::Ongoing, this, &APlayerCharacter::OnIA_InteractOngoing);
			Input->BindAction(IA_Interact, ETriggerEvent::Completed, this, &APlayerCharacter::OnIA_InteractOngoing);
		}
	}
}

// (4.1)

	void APlayerCharacter::OnIA_InteractStarted()
	{
		InteractionComponent->InteractBegin();
	}
	
// (4.2)
void APlayerCharacter::OnIA_InteractOngoing(const FInputActionInstance& Instance)
{
	float ElapsedSeconds = Instance.GetElapsedTime();
	InteractionComponent->OnInteractionPressOngoing.Broadcast(ElapsedSeconds);
}

// (4.3)
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

/* ------------------------------ Enhanced Input handler-functions block ------------------------------- */
/* ------------------------------ MoveAction handler-function (5) ------------------------------- */
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White, TEXT("Move action"));

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

/* ------------------------------ LookAction handler-function (6) ------------------------------- */
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White, TEXT("Look action"));

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

/* ------------------------------ JumpAction handler-function (7) ------------------------------- */
void APlayerCharacter::Jump()
{
	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White, TEXT("Jump action"));

	ACharacter::Jump();
}
