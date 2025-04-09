// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputDataConfig.h"
#include "PlayerCharacter.generated.h"

/**------------------------------ Forward declaration block begin------------------------------- **/
// This block serves as "I know, there WILL BE some class which will be used in blueprints, but they are not #included yet"
class UInteractionComponent;
class UInventoryComponent;
/**------------------------------ Forward declaration block end------------------------------- **/

UCLASS()
class COTAA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	/**------------------------------ Components block------------------------------- **/

	UPROPERTY(VisibleAnywhere, Category = "EnhancedInput")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "EnhancedInput")
	class UCameraComponent* Camera;
	/**------------------------------ Enhanced Input Block------------------------------- **/
protected:
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputDataConfig* InputConfig;

	/**------------------------------ Constructor ------------------------------- **/
public:
	APlayerCharacter();

	/**------------------------------ BeginPlay ------------------------------- **/
protected:
	virtual void BeginPlay() override;
	/**------------------------------ Tick event ------------------------------- **/
public:
	virtual void Tick(float DeltaTime) override;

	/**------------------------------ Enhanced Input setup function ------------------------------- **/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**----------- IA Handle functions block ----------- **/
protected:
	// MoveAction handler
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	// LookAction handler
	UFUNCTION()
	void Look(const FInputActionValue& Value);

	// InteractAction handler
	void Jump();

private:
	/**------------------------------ Custom Components block ------------------------------- **/
	/** ----------- Interaction component ----------- **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInteractionComponent* InteractionComponent;

public:
	// handles InteractionComponent behavior on started action
	void OnIA_InteractStarted();

	// handles InteractionComponent on ongoing action
	void OnIA_InteractOngoing(const FInputActionInstance& Instance);

	// handles InteractionComponent behavior on completed action
	void OnIA_InteractCompleted();

	/** ----------- Inventory component ----------- **/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	UInventoryComponent* GetInventoryComponent() const;
};
