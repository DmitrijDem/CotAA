// Fill out your copyright notice in the Description page of Project Settings.
/*
This component took like 2 full days of work :(
I just hate how it is easy to make some things inside blueprints and how it's hard to do with C++
*/

#include "InteractionSys/InteractionComponent.h"
#include "GameFramework/Character.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
/* ------------------------------ Components Libraries------------------------------- */
#include "Components/CapsuleComponent.h"
/* ------------------------------ Custom Libraries------------------------------- */
#include "InteractionSys/Interactable.h"


// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	//// Find out who is components owner (Could be any Character (Player and NPCs))
	//Owner = Cast<ACharacter>(GetOwner());

	//// Set this component to be initialized when the game starts, and to be ticked every frame.
	//PrimaryComponentTick.bCanEverTick = true;

	//ConstructorHelpers::FClassFinder<UUserWidget> WBP_Interaction_ClassFinder(TEXT("/Game/Player/UI/WBP_InteractionHint"));

	//if (WBP_Interaction_ClassFinder.Succeeded())
	//{
	//	WidgetClass = WBP_Interaction_ClassFinder.Class;
	//}
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	//// Setting capsule component for interactions
	//if (Cast<ACharacter>(Owner))
	//{
	//	UCapsuleComponent* CapsuleComp = Owner->GetCapsuleComponent();

	//	// This set ups any Interactor capsule component, NPCs as well - so they will be able to interact with something like doors etc.
	//	if (CapsuleComp)
	//	{
	//		GEngine->AddOnScreenDebugMessage(2, 10.0f, FColor::White, TEXT("Setting up overlaps inside component"));
	//		CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::HandleCapsuleComponentOverlapBegin);
	//		CapsuleComp->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::HandleCapsuleComponentOverlapEnd);
	//	}

	//	if (!WidgetComponent) {
	//		// Widget component creation
	//		WidgetComponent = NewObject<UWidgetComponent>(this, UWidgetComponent::StaticClass(), TEXT("InteractionWidgetComponent"), RF_Transient);
	//		// Registration
	//		WidgetComponent->RegisterComponent();
	//		// ManualAttachment = true
	//		WidgetComponent->SetupAttachment(nullptr);
	//		// Using player screen to show widget
	//		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	//		// Widget size (actually, it's pretty small for 1920x1080 - adjust it)
	//		WidgetComponent->SetDrawSize(FVector2D(250, 30));
	//	}
	//}
}

/* ------------------------------ Interaction handler-function ------------------------------- */
// This function must be called once on one interactable object
void UInteractionComponent::Interact()
{
	//// Calls Interact(AActor* Interactor) on object from one of Interactibles near Interactor
	//if (InteractablesInRange.Num() > 0)
	//{
	//	// Possible, there will be not a single non implemented with UInteractable Actor in array, but just to be sure - safety check
	//	AActor* InteractableActor = GetActiveInteractable();

	//	if (InteractableActor->Implements<UInteractable>())
	//	{
	//		IInteractable::Execute_Interact(InteractableActor, Owner);
	//	}
	//}
}
/* ------------------------------ Widget Render handler-function ------------------------------- */
// Creates WBP_Interaction_Hint Widget or clears it
// Called once on OnBeginOverlap and OnEndOverlap to add or clear WidgetComponent
// Adds "Press *button* to *Action* to players screen above interactable
void UInteractionComponent::RenderInteractionWidget()
{
	//if (!InteractablesInRange.IsEmpty())
	//{
	//	UWorld* World = GetWorld();

	//	if (World && WidgetComponent)
	//	{
	//		UUserWidget* InteractionHintWidget = CreateWidget(World, WidgetClass);
	//		if (InteractionHintWidget)
	//		{
	//			WidgetComponent->SetWidget(InteractionHintWidget);
	//			AActor* ActiveInteractable = GetActiveInteractable();
	//			WidgetComponent->SetWorldLocation(ActiveInteractable->GetActorLocation());
	//		}
	//	}
	//}
	//else
	//{
	//	// I need to check it, because if, for any reason, widget isn't set - it will crush game
	//	if (WidgetComponent) WidgetComponent->SetWidget(nullptr);
	//}
}

AActor* UInteractionComponent::GetActiveInteractable()
{
	//if (!InteractablesInRange.IsEmpty())
	//{
	//	return InteractablesInRange.Last();
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("GetActiveInteractable() was called on empty Interactables In Range Array!"))
			return nullptr;
	//}
}

/* ------------------------------ OnBeginOverlap event ------------------------------- */
/**
* Function which handles actors overlapping with ACharacter capsule, placing actors into InteractablesInRange if must
* Must be used once for every actor which began overlapping with capsule
*/
void UInteractionComponent::HandleCapsuleComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("BeginOverlap actor to interact"));
	if (OtherActor && OtherActor->Implements<UInteractable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("Added actor to interact"));
		InteractablesInRange.AddUnique(OtherActor);
		RenderInteractionWidget();
	}*/
}

/* ------------------------------ OnEndOverlap event ------------------------------- */
/**
* Function which handles actors which stopped overlapping with player capsule, removing actors from InteractablesInRange if must
* Must be used once for every actor which stopped overlapping with capsule
*/
void UInteractionComponent::HandleCapsuleComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("EndOverlap actor to interact"));
	//if (OtherActor && OtherActor->Implements<UInteractable>())
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("Removed actor to interact"));
	//	InteractablesInRange.Remove(OtherActor);
	//	RenderInteractionWidget();
	//}
}

