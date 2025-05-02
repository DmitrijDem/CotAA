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
}

/* ------------------------------ Tick ------------------------------- */
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UInventoryComponent* APlayerCharacter::GetInventoryComponent() const
{
	if (InventoryComponent)
	{
		return Cast<UInventoryComponent>(GetComponentByClass(UInventoryComponent::StaticClass()));
	}

	return nullptr;
}

UInteractionComponent* APlayerCharacter::GetInteractionComponent() const
{
	if (InteractionComponent)
	{
		return Cast<UInteractionComponent>(GetComponentByClass(UInteractionComponent::StaticClass()));
	}

	return nullptr;
}
