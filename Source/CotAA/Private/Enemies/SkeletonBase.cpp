
// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/SkeletonBase.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASkeletonAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ASkeletonAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (BehaviorTree->IsValidLowLevel())
	{
		BehaviorTree = LoadObject<UBehaviorTree>(
			nullptr,
			TEXT("/Game/Enemies/Skeletons/BT_SkeletonBase.BT_SkeletonBase"));
	}

	RunBehaviorTree(BehaviorTree);

	if (Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

ASkeletonBase::ASkeletonBase()
{
	GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, TEXT("/Game/Player/Character/Mesh/SK_Mannequin")));
	UMaterialInterface* GreenMaterial = (LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Enemies/Skeletons/Materials/M_SkeletonMannequin")));

	GetMesh()->SetMaterial(0, GreenMaterial);

	CharacterStats->DefaultStats.Health = 80.0f;
	CharacterStats->DefaultStats.Armor = 5.0f;
}

void ASkeletonBase::BeginPlay()
{
	Super::BeginPlay();

	AttackHitBox->OnComponentBeginOverlap.AddDynamic(this, &ASkeletonBase::OnAttackHit);
}

void ASkeletonBase::Attack()
{
	Super::Attack();

	//PlayAnimMontage(AttackAniMontage);
}

void ASkeletonBase::OnAttackHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor->Implements<UDamageable>())
	{
		IDamageable::Execute_TakeDamage(OtherActor, 10.0f, nullptr, this);
	}
	
}