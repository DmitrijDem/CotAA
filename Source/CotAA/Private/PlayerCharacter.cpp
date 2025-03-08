// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

/* ------------------------------ Enhanced Input Libraries------------------------------- */
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
/* ------------------------------ Components Libraries------------------------------- */
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
/* ------------------------------ Custom Libraries------------------------------- */

#include "InteractionSys/Interactable.h"

/* ------------------------------ Debug Libraries------------------------------- */
#include "DrawDebugHelpers.h"

/* ------------------------------ Constructor ------------------------------- */
APlayerCharacter::APlayerCharacter()
{
	// It is set to true because I might need Tick() for player
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	// Setting up spring arm and camera 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpirngArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
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

/* ------------------------------ Enhanced Input Setup ------------------------------- */
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		Input->BindAction(InteractAction, ETriggerEvent::Started , this, &APlayerCharacter::Interact);
	}

	// Setting capsule component for interactions

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

	if (CapsuleComp)
	{
		CapsuleComp->SetGenerateOverlapEvents(true);
		CapsuleComp->SetCollisionProfileName(TEXT("Pawn"));
		GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Red, TEXT("Setting up overlaps"));
		CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
		CapsuleComp->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);
	}

}

/* ------------------------------ MoveAction handler-function ------------------------------- */
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Red, TEXT("Move action"));

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

	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Red, TEXT("Look action"));

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

/* ------------------------------ JumpAction handler-function ------------------------------- */
void APlayerCharacter::Jump()
{
	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Red, TEXT("Jump action"));

	ACharacter::Jump();
}

/* ------------------------------ InteractAction handler-function ------------------------------- */
void APlayerCharacter::Interact()
{
	GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::Red, TEXT("E pressed"));

	// If *Interaction key* (Default: E) was pressed - calls Interact(AActor* Interactor) on object from one of Interactibles near player
	// After some tries - this is best solution, maybe
	if (InteractablesInRange.Num() > 0)
	{
		AActor* InteractableActor = InteractablesInRange[0];

		if (InteractableActor->Implements<UInteractable>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Interact(this)"));
			IInteractable::Execute_Interact(InteractableActor, this);
		}
	}
}

/* ------------------------------ OnBeginOverlap event ------------------------------- */
/**
* Function which handles actors overlapping with player capsule, placing actors into InteractablesInRange if must
* Must be used once for every actor which began overlapping with capsule
*/
void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("BeginOverlap actor to interact"));
	if (OtherActor && OtherActor->Implements<UInteractable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Added actor to interact"));
		InteractablesInRange.AddUnique(OtherActor);
	}

}

/* ------------------------------ OnEndOverlap event ------------------------------- */
/**
* Function which handles actors which stopped overlapping with player capsule, removing actors from InteractablesInRange if must
* Must be used once for every actor which stopped overlapping with capsule
*/
void APlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("EndOverlap actor to interact"));
	if (OtherActor && OtherActor->Implements<UInteractable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Removed actor to interact"));
		InteractablesInRange.Remove(OtherActor);
	}
}
