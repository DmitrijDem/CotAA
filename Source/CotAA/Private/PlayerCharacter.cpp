// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
/* ------------------------------ Enhanced Input Libraries------------------------------- */
#include "GameFramework/CharacterMovementComponent.h"
/* ------------------------------ Components Libraries------------------------------- */
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
/* ------------------------------ Custom Libraries------------------------------- */
#include "InteractionSystem/InteractionComponent.h"
#include "InteractionSystem/InventoryComponent.h"

/* ------------------------------ Constructor ------------------------------- */
APlayerCharacter::APlayerCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	RootComponent = GetCapsuleComponent();

	// Setting up spring arm and camera 
	ConfigureCamera();
	
	// Setting capsule component for interactions
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();

	// Interaction Component
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");

	// Inventory Component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("InventoryComponent");

	// PlayerStats Component
	PlayerStatsComponent = CreateDefaultSubobject<UCharacterStatsComponent>("PlayerStatsComponent");
}

void APlayerCharacter::ConfigureCamera()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;
	
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->SocketOffset = FVector(0.0f, 50.0f, 50.0f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 8.0f;
	SpringArm->bDoCollisionTest = false;

	SpringArm->CameraLagMaxDistance = 100.0f;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetFieldOfView(85.f);
}


/* ------------------------------ BeginPlay ------------------------------- */
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

/* ------------------------------ Tick ------------------------------- */
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UInteractionComponent* APlayerCharacter::GetInteractionComponent() const
{
	if (InteractionComponent)
	{
		return Cast<UInteractionComponent>(GetComponentByClass(UInteractionComponent::StaticClass()));
	}

	return nullptr;
}