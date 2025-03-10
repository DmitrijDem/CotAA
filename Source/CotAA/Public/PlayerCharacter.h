// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

	/* ------------------------------ Forward declaration block begin------------------------------- */
// This block serves as "I know, there WILL BE some class which will be used in blueprints, but they are not #include here to clean the code and space"
class UInteractionComponent;
/* ------------------------------ Forward declaration block end------------------------------- */
UCLASS()
class COTAA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	/* ------------------------------ Components block------------------------------- */

	UPROPERTY(VisibleAnywhere, Category = "EnhancedInput")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "EnhancedInput")
	class UCameraComponent* Camera;
	/* ------------------------------ Enhanced Input Block------------------------------- */
protected:

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* InteractAction;

	/* ------------------------------ Constructor ------------------------------- */
public:
	APlayerCharacter();

	/* ------------------------------ BeginPlay ------------------------------- */
protected:
	virtual void BeginPlay() override;
	/* ------------------------------ Tick event ------------------------------- */
public:	
	virtual void Tick(float DeltaTime) override;

	/* ------------------------------ Enhanced Input setup function ------------------------------- */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/* ------------------------------ Interaction block ------------------------------- */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
//    UInteractionComponent* InteractionComponent;	

public:

	// Capsule component overlap events to add objects from array
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Capsule component overlap event to delete objects from array
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Function that handles interactions with UInteractible-implemented actors
	UFUNCTION()
	void OnInteract();

	// MoveAction handler
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	// LookAction handler
	UFUNCTION()
	void Look(const FInputActionValue& Value);

	// InteractAction handler
	void Jump();

};
