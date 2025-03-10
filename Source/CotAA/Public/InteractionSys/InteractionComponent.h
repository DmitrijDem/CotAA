// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"

#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COTAA_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:

	// Owner of this component
	ACharacter* Owner;


	/* ------------------------------ Interaction system variables block ------------------------------- */
	// Array of Actor* objects near player to interact with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactables")
	TArray<AActor*> InteractablesInRange;

	UPROPERTY()
	UWidgetComponent* WidgetComponent;

	UPROPERTY()
	TSubclassOf<class UUserWidget> WidgetClass;

	/* ------------------------------ Interaction system functions block ------------------------------- */
	// Function to handle IA_Interact or NPC calls
	UFUNCTION(BlueprintCallable, Category = "InteractionFunction")
	void Interact();

	// Function to render InteractionWidgetComponent
	UFUNCTION(BlueprintCallable, Category = "InteractionWidget")
	void RenderInteractionWidget();

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

