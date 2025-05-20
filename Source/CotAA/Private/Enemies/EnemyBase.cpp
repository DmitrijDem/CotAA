// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyBase.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterStats = CreateDefaultSubobject<UCharacterStatsComponent>("CharacterStats");
	// HealthWidget construct
	AttackHitBox = CreateDefaultSubobject<UBoxComponent>("AttackHitBox");
	AttackHitBox->SetupAttachment(GetMesh(), "hand_r");

	SetupStarterComponents();
}

void AEnemyBase::SetupStarterComponents()
{
	AttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackHitBox->SetBoxExtent(FVector(10.0f, 30.0f, 30.0f));
}


void AEnemyBase::OnAttackHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AEnemyBase::TakeDamage_Implementation(float Damage, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (!CharacterStats) return;
	
	float ActualDamage = FMath::Max(Damage - CharacterStats->CurrentStats.Armor, 0.0f);
	CharacterStats->CurrentStats.Health -= ActualDamage;

	if (CharacterStats->CurrentStats.Health <= 0.0f)
	{
		OnDeath();
	}
}

void AEnemyBase::OnDeath_Implementation()
{
	// Play animation, sound etc.
	Destroy();
}

void AEnemyBase::Attack()
{
	if (!AttackHitBox) return;

	AttackHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttackHitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		AttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}, 0.1f, false);
}

// Sadly, using behaviour tree to create enemies - I think, impossible to recreate in C++, so I just put here functions I need at BP_"Enemy" to control enemies behaviour
void AEnemyBase::UpdateWalkSpeed(float NewWalkSpeed)
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->MaxWalkSpeed = NewWalkSpeed;
	}
}