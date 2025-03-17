// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
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
	class UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Jump;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Interact;
	
	/* ------------------------------ Constructor (1) ------------------------------- */
public:
	APlayerCharacter();

	/* ------------------------------ BeginPlay (2) ------------------------------- */
protected:
	virtual void BeginPlay() override;
	/* ------------------------------ Tick event (3) ------------------------------- */
public:	
	virtual void Tick(float DeltaTime) override;

	/* ------------------------------ Enhanced Input setup function (4) ------------------------------- */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// MoveAction handler (5)
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	// LookAction handler (6)
	UFUNCTION()
	void Look(const FInputActionValue& Value);

	// InteractAction handler (7)
	void Jump();
};
