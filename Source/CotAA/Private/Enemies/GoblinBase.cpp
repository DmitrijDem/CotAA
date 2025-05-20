// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/GoblinBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AGoblinAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AGoblinAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree->IsValidLowLevel())
	{
		BehaviorTree = LoadObject<UBehaviorTree>(
			nullptr,
			TEXT("/Game/Enemies/Goblins/BT_GoblinBase.BT_GoblinBase"));
	}

	RunBehaviorTree(BehaviorTree);

	if (Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

AGoblinBase::AGoblinBase()
{
	GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Player/Character/Mesh/SK_Mannequin")));
	UMaterialInterface* GreenMaterial = (LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Enemies/Goblins/Materials/M_GoblinMannequin")));

	GetMesh()->SetMaterial(0, GreenMaterial);

	CharacterStats->DefaultStats.Health = 80.0f;
	CharacterStats->DefaultStats.Armor = 5.0f;
}

void AGoblinBase::BeginPlay()
{
	Super::BeginPlay();

	AttackHitBox->OnComponentBeginOverlap.AddDynamic(this, &AGoblinBase::OnAttackHit);
}

void AGoblinBase::Attack()
{
	Super::Attack();

	//PlayAnimMontage(AttackAniMontage);
}

void AGoblinBase::OnAttackHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor->Implements<UDamageable>())
	{
		IDamageable::Execute_TakeDamage(OtherActor, 10.0f, nullptr, this);
	}
	
}

