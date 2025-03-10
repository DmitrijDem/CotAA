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
// Yes, this #include impossible to avoid :(
#include "InteractionSys/InteractionComponent.h"
/* ------------------------------ Constructor ------------------------------- */
APlayerCharacter::APlayerCharacter()
{
	//// It is set to true because I might need Tick() for player
	//PrimaryActorTick.bCanEverTick = true;

	//RootComponent = GetCapsuleComponent();

	//// Setting up spring arm and camera 
	//SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpirngArm");
	//SpringArm->SetupAttachment(RootComponent);
	//SpringArm->bUsePawnControlRotation = true;

	//Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	//Camera->SetupAttachment(SpringArm);

	//bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bOrientRotationToMovement = false;

	// Interaction Component
//	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
}

/* ------------------------------ BeginPlay ------------------------------- */
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	//{
	//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//	{
	//		Subsystem->AddMappingContext(InputMapping, 0);
	//	}
	//}


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

	//if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	//{
	//	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	//	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	//	Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
	//	Input->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::OnInteract);
	//}

	//// Setting capsule component for interactions

	//UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

	//if (CapsuleComp)
	//{
	//	CapsuleComp->SetGenerateOverlapEvents(true);
	//	CapsuleComp->SetCollisionProfileName(TEXT("Pawn"));
	//	GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Red, TEXT("Setting up overlaps"));
	//	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	//	CapsuleComp->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);
	//}
}

/* ------------------------------ Enhanced Input handler-functions block ------------------------------- */

// Function that handles interactions with UInteractible-implemented actors
void APlayerCharacter::OnInteract()
{
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("Trying to call Interact from component"));

	//if (InteractionComponent)
	//{
	//	InteractionComponent->Interact();
	//}
}

/* ------------------------------ MoveAction handler-function ------------------------------- */
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	//FVector2D InputVector = Value.Get<FVector2D>();

	//GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White, TEXT("Move action"));

	//if (IsValid(Controller))
	//{
	//	// Get Forward Direction
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//	// Add movement input
	//	AddMovementInput(ForwardDirection, InputVector.Y);
	//	AddMovementInput(RightDirection, InputVector.X);
	//}
}

/* ------------------------------ LookAction handler-function ------------------------------- */
void APlayerCharacter::Look(const FInputActionValue& Value)
{
	//FVector2D InputVector = Value.Get<FVector2D>();

	//GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White, TEXT("Look action"));

	//if (IsValid(Controller))
	//{
	//	AddControllerYawInput(InputVector.X);
	//	AddControllerPitchInput(InputVector.Y);
	//}
}

/* ------------------------------ JumpAction handler-function ------------------------------- */
void APlayerCharacter::Jump()
{
	//GEngine->AddOnScreenDebugMessage(1, 0.1f, FColor::White, TEXT("Jump action"));

	//ACharacter::Jump();
}

/* ------------------------------ OnBeginOverlap event ------------------------------- */
/**
* Function which handles actors overlapping with player capsule
*/
void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


}

/* ------------------------------ OnEndOverlap event ------------------------------- */
/**
* Function which handles actors which stopped overlapping with player capsule
*/
void APlayerCharacter::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
