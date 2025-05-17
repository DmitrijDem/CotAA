// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem/InteractionComponent.h"
#include "GameFramework/Character.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

/**------------------------------ Components Libraries------------------------------- **/
#include "Components/CapsuleComponent.h"
/**------------------------------ Custom Libraries------------------------------- **/
#include "InteractionSystem/Interactable.h"
#include "InteractionSystem/InventoryComponent.h"
#include "./Enums/InteractBehavior/InteractionType.h"
#include "Enums/InteractBehavior/InteractionWith.h"
#include "Misc/OutputDeviceNull.h"

/**------------------------------ Constructor ------------------------------- **/
UInteractionComponent::UInteractionComponent()
{
	// Find out who is components owner (Must be player)
	Owner = Cast<ACharacter>(GetOwner());

	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UUserWidget> WBP_Interaction_ClassFinder(
		TEXT("/Game/UI/Inventory_Interactions/WBP_InteractionHint"));

	if (WBP_Interaction_ClassFinder.Succeeded())
	{
		WidgetClass = WBP_Interaction_ClassFinder.Class;
	}
}


/**------------------------------ BeginPlay ------------------------------- **/
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwnerPawn = GetOwner();
	if (!OwnerPawn) return;
	
	// Setting capsule component for interactions
	if (ACharacter* OwnerChar = Cast<ACharacter>(OwnerPawn))
	{
		if (UCapsuleComponent* CapsuleComponent = Cast<ACharacter>(OwnerChar)->GetCapsuleComponent())
		{
			// This set-ups Interactor capsule component
			CapsuleComponent->OnComponentBeginOverlap.AddDynamic(
				this, &UInteractionComponent::HandleCapsuleComponentOverlapBegin);
			CapsuleComponent->OnComponentEndOverlap.AddDynamic(
				this, &UInteractionComponent::HandleCapsuleComponentOverlapEnd);

			if (!InteractionWidgetComponent)
			{
				// Widget component creation
				InteractionWidgetComponent = NewObject<UWidgetComponent>(this, UWidgetComponent::StaticClass(),
																		 TEXT("InteractionWidgetComponent"), RF_Transient);
				// Registration
				InteractionWidgetComponent->RegisterComponent();
				// ManualAttachment = true
				InteractionWidgetComponent->SetupAttachment(nullptr);
				// Using player screen to show widget
				InteractionWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
				// Widget size (actually, it's pretty small for 1920x1080 - adjust it)
				InteractionWidgetComponent->SetDrawSize(FVector2D(100, 100));
			}
		}
	}
}

/**------------------------------ Function to handle interaction key press ongoing event dispatcher calls ------------------------------- **/
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

	// If player holds button long enough - execute Interact and remove subscription
	if (ElapsedSeconds > IInteractable::Execute_GetHoldDuration(GetActiveInteractable()))
	{
		InteractWithActiveInteractable();
		OnInteractionPressOngoing.RemoveDynamic(this, &UInteractionComponent::InteractionOngoingHandler);
	}
}

/**------------------------------ Interaction handler-function ------------------------------- **/
// This function must be called once on one interactable object
void UInteractionComponent::InteractWithActiveInteractable()
{
	// Calls Interact(AActor* Interactor) on object from one of Interactibles near Interactor
	if (IsValid(GetActiveInteractable()))
	{
		AActor* InteractableActor = GetActiveInteractable();

		EInteractionWith Object = IInteractable::Execute_GetInteractWith(InteractableActor);

		// Checking with what player interacts
		// Comment: at first, I thought, that creating InteractLootable and give to parameters UInventoryComponent
		// Is a good idea, but then I decided to add GetInventoryComponent to player, so
		// It's just a same function as Interact, but, now, on loot Interactables, I can simply make 2 different
		// actions, so I'll leave it as it is, in case of future changes
		if (InteractableActor->Implements<UInteractable>())
		{
			switch (Object)
			{
			case EInteractionWith::LootItem:
				{
					IInteractable::Execute_InteractLootable(InteractableActor, Owner);
					break;
				}
			case EInteractionWith::Harvestable:
				{
					IInteractable::Execute_InteractLootable(InteractableActor, Owner);
					break;
				}
			case EInteractionWith::Door:
				{
					IInteractable::Execute_Interact(InteractableActor, Owner);
					break;
				}
			default:
				// Nothing, but I can add something here to somehow show that something went wrong, I guess
				break;
			}
		}
	}
}

/**------------------------------ Function to handle press and hold interactables ------------------------------- **/
void UInteractionComponent::RequestInteraction()
{
	if (IsValid(GetActiveInteractable()))
	{
		AActor* InteractableActor = GetActiveInteractable();

		if (InteractableActor->Implements<UInteractable>())
		{
			// Find which type interactable has (/Interactable.h - UEnum)
			// Depending on type
			// Press - interact with interactable immediately
			// Hold - wait until dispatcher event fires and then interact
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

/**------------------------------ Function to get Active (last in array) interactable actor ------------------------------- **/
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

/**------------------------------ Widget Render handler-function ------------------------------- **/
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
				FProperty* InteractionTypeProperty = InteractionWidgetRef->GetClass()->FindPropertyByName(
					TEXT("InteractionType"));
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

/**------------------------------ OnBeginOverlap event ------------------------------- **/
/**
* Function which handles actors overlapping with ACharacter capsule, placing actors into InteractablesInRange if must
* Must be used once for every actor which began overlapping with capsule
**/
void UInteractionComponent::HandleCapsuleComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent,
                                                               AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                                               int32 OtherBodyIndex, bool bFromSweep,
                                                               const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->Implements<UInteractable>())
	{
		InteractablesInRange.AddUnique(OtherActor);
		RenderInteractionWidget();
	}
}

/**------------------------------ OnEndOverlap event ------------------------------- **/
/**
* Function which handles actors which stopped overlapping with player capsule, removing actors from InteractablesInRange if must
* Must be used once for every actor which stopped overlapping with capsule
**/
void UInteractionComponent::HandleCapsuleComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent,
                                                             AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                                             int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->Implements<UInteractable>())
	{
		InteractablesInRange.Remove(OtherActor);
		RenderInteractionWidget();
	}
}
