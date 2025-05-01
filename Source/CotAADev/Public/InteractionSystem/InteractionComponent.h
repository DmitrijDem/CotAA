// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionPressOngoing, float, ElapsedSeconds);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COTAADEV_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/* ------------------------------ Constructor (1) ------------------------------- */
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	/* ------------------------------ BeginPlay (2) ------------------------------- */
	virtual void BeginPlay() override;
	
public:

	/* ------------------------------ Event Dispatcher (OnInteractionPressOngoing) ------------------------------- */
	// Manages holding interaction key
	UPROPERTY(BlueprintAssignable, Category="Interaction")
	FOnInteractionPressOngoing OnInteractionPressOngoing;

	/* ------------------------------ OnInteractionPressOngoing-handler (3) ------------------------------- */
	UFUNCTION()
	void InteractionOngoingHandler(float ElapsedSeconds);
	
	/* ------------------------------ Interaction system variables block ------------------------------- */
	
	// Owner of this component
	ACharacter* Owner;
	
	// Array of Actor* objects near player to interact with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactables")
	TArray<AActor*> InteractablesInRange;

	// Widget which describes shows on Interactable Root when player can interact with it
	// Widget Component to create and show player
	UPROPERTY()
	UWidgetComponent* InteractionWidgetComponent;

	// Widget to show (created using BP)
	UPROPERTY()
	UUserWidget* InteractionWidgetRef;

	// Widget class to find InteractionWidgetRef
	UPROPERTY()
	TSubclassOf<class UUserWidget> WidgetClass;

	/* ------------------------------ Interaction system functions block ------------------------------- */
	
	// Function to render InteractionWidgetComponent
	UFUNCTION(BlueprintCallable, Category = "InteractionWidget")
	void RenderInteractionWidget();
	
	// Function to handle IA_Interact
	UFUNCTION(BlueprintCallable, Category = "InteractionFunction")
	void RequestInteraction();
	
	// Function to handle IA_Interact
	UFUNCTION(BlueprintCallable, Category = "InteractionFunction")
	void InteractWithActiveInteractable();
	
	//Function to get active (last) interactable in array
	UFUNCTION(BlueprintPure, Category = "InteractionWidget")
	AActor* GetActiveInteractable();

public:

	// Capsule component begin overlap
	UFUNCTION()
	void HandleCapsuleComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Capsule component end overlap
	UFUNCTION()
	void HandleCapsuleComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};