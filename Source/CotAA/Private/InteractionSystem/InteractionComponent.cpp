// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem/InteractionComponent.h"
#include "GameFramework/Character.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

/* ------------------------------ Components Libraries------------------------------- */
#include "Components/CapsuleComponent.h"
/* ------------------------------ Custom Libraries------------------------------- */
#include "EnhancedInputSubsystems.h"
#include "InteractionSystem/Interactable.h"
#include "Misc/OutputDeviceNull.h"

/* ------------------------------ Constructor (1) ------------------------------- */
UInteractionComponent::UInteractionComponent()
{
	// Find out who is components owner (Could be any Character (Player and NPCs))
	Owner = Cast<ACharacter>(GetOwner());

	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UUserWidget> WBP_Interaction_ClassFinder(TEXT("/Game/Player/UI/WBP_InteractionHint"));

	if (WBP_Interaction_ClassFinder.Succeeded())
	{
		WidgetClass = WBP_Interaction_ClassFinder.Class;
	}
}


/* ------------------------------ BeginPlay (2) ------------------------------- */
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Setting capsule component for interactions
	if (UCapsuleComponent* CapsuleComponent = Cast<ACharacter>(Owner)->GetCapsuleComponent())
	{
		// This set-ups any Interactor capsule component, NPCs as well - so they will be able to interact with something like doors etc.
		GEngine->AddOnScreenDebugMessage(2, 10.0f, FColor::White, TEXT("Setting up overlaps inside component"));
		CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &UInteractionComponent::HandleCapsuleComponentOverlapBegin);
		CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &UInteractionComponent::HandleCapsuleComponentOverlapEnd);

		if (!InteractionWidgetComponent) {
			// Widget component creation
			InteractionWidgetComponent = NewObject<UWidgetComponent>(this, UWidgetComponent::StaticClass(), TEXT("InteractionWidgetComponent"), RF_Transient);
			// Registration
			InteractionWidgetComponent->RegisterComponent();
			// ManualAttachment = true
			InteractionWidgetComponent->SetupAttachment(nullptr);
			// Using player screen to show widget
			InteractionWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
			// Widget size (actually, it's pretty small for 1920x1080 - adjust it)
			InteractionWidgetComponent->SetDrawSize(FVector2D(250, 30));
		}
	}
}

/* ------------------------------ Function to handle interaction key press ongoing event dispatcher calls ------------------------------- */
// Demyanenko D.A. 17.03.2025
// Comment: I wasted 3! days (lucky, that I decided to make some documentation in parallel) to find out that in InteractionComponent, instead of ProcessEvent
// I would need to use: FString Command = FString::Printf(TEXT("SetProgressPercent %f"), Percent);
// InteractionWidgetRef->CallFunctionByNameWithArguments(*Command, OutputDeviceNull, nullptr, true);
// ProcessEvent - worked, but it didn't translate Percent to ProgressBar as parameter by unknown reason and it was always set to 0

void UInteractionComponent::InteractionOngoingHandler(float ElapsedSeconds)
{
	
	if (IsValid(InteractionWidgetRef))
	{
		if (InteractionWidgetRef->FindFunction("SetProgressPercent"))
		{
			FOutputDeviceNull OutputDeviceNull;
			float Percent = ElapsedSeconds / IInteractable::Execute_GetHoldDuration(GetActiveInteractable());
			FString Command = FString::Printf(TEXT("SetProgressPercent %f"), Percent);
			InteractionWidgetRef->CallFunctionByNameWithArguments(*Command, OutputDeviceNull, nullptr, true);
		}
	}
	else
	{
		// Nothing
	}

	if (ElapsedSeconds > IInteractable::Execute_GetHoldDuration(GetActiveInteractable()))
	{
		InteractWithActiveInteractable();
		OnInteractionPressOngoing.RemoveDynamic(this, &UInteractionComponent::InteractionOngoingHandler);
	}
	
}
/* ------------------------------ Interaction handler-function ------------------------------- */
// This function must be called once on one interactable object
void UInteractionComponent::InteractWithActiveInteractable()
{
	// Calls Interact(AActor* Interactor) on object from one of Interactibles near Interactor
	if (IsValid(GetActiveInteractable()))
	{
		AActor* InteractableActor = GetActiveInteractable();

		if (InteractableActor->Implements<UInteractable>())
		{
			// Interaction Animation must be added here
			IInteractable::Execute_Interact(InteractableActor, Owner);
		}
	}
}

/* ------------------------------ Function to handle press and hold interactables ------------------------------- */
void UInteractionComponent::InteractBegin()
{
	if (IsValid(GetActiveInteractable()))
	{
		AActor* InteractableActor = GetActiveInteractable();

		if (InteractableActor->Implements<UInteractable>())
		{
			// Find which type interactable has (/Interactable.h - UEnum)
			// Depending on type
			// Press - interact with interactable immediatly
			// Hold - wait untill dispatcher event fires and then interact
			switch (IInteractable::Execute_GetInteractionType(InteractableActor))
			{
			case(EInteractableType::Press):
				{
					InteractWithActiveInteractable();
					break;
				}
			case(EInteractableType::Hold):
				{
					OnInteractionPressOngoing.AddDynamic(this, &UInteractionComponent::InteractionOngoingHandler);
					break;
				}
			}
		}
	}
}

/* ------------------------------ Function to get Active (last in array) interactable actor ------------------------------- */
AActor* UInteractionComponent::GetActiveInteractable()
{
	if (!InteractablesInRange.IsEmpty())
	{
		return InteractablesInRange.Last();
	}
	else
	{
		return nullptr;
	}
}

/* ------------------------------ Widget Render handler-function ------------------------------- */
// Creates WBP_Interaction_Hint Widget or clears it
// Called once on OnBeginOverlap and OnEndOverlap to add or clear WidgetComponent
// Adds "Press *button* to *Action* to players screen above interactable"
void UInteractionComponent::RenderInteractionWidget()
{
	if (IsValid(GetActiveInteractable()))
	{
		AActor* ActiveInteractable = GetActiveInteractable();
		UWorld* World = GetWorld();

		if (World && InteractionWidgetComponent)
		{
			InteractionWidgetRef = CreateWidget(World, WidgetClass);
			if (InteractionWidgetRef)
			{
				FProperty* InteractionTypeProperty = InteractionWidgetRef->GetClass()->FindPropertyByName(TEXT("InteractionType"));
				if (InteractionTypeProperty)
				{
					EInteractableType InteractionType = IInteractable::Execute_GetInteractionType(ActiveInteractable);
					InteractionTypeProperty->SetValue_InContainer(InteractionWidgetRef, &InteractionType);
				}
				InteractionWidgetComponent->SetWidget(InteractionWidgetRef);
				InteractionWidgetComponent->SetWorldLocation(ActiveInteractable->GetActorLocation());
			}
		}
	}
	else
	{
		// I need to check it, because if, for any reason, widget isn't set - it will crush game
		if (InteractionWidgetComponent) InteractionWidgetComponent->SetWidget(nullptr);
	}
}

/* ------------------------------ OnBeginOverlap event ------------------------------- */
/**
* Function which handles actors overlapping with ACharacter capsule, placing actors into InteractablesInRange if must
* Must be used once for every actor which began overlapping with capsule
*/
void UInteractionComponent::HandleCapsuleComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("BeginOverlap actor to interact"));
	if (OtherActor && OtherActor->Implements<UInteractable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("Added actor to interact"));
		InteractablesInRange.AddUnique(OtherActor);
		RenderInteractionWidget();
	}
}

/* ------------------------------ OnEndOverlap event ------------------------------- */
/**
* Function which handles actors which stopped overlapping with player capsule, removing actors from InteractablesInRange if must
* Must be used once for every actor which stopped overlapping with capsule
*/
void UInteractionComponent::HandleCapsuleComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("EndOverlap actor to interact"));
	if (OtherActor && OtherActor->Implements<UInteractable>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::White, TEXT("Removed actor to interact"));
		InteractablesInRange.Remove(OtherActor);
		RenderInteractionWidget();
	}
}