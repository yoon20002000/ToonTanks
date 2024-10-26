// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Tank Collider");
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turret Mesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	
}

void ABasePawn::RotateTurret(const FVector& InLookAtTarget) const
{
	const FVector ToTarget = InLookAtTarget - TurretMesh->GetComponentLocation();
	const FRotator LookAtRotation = FRotator(0, ToTarget.Rotation().Yaw, 0);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation,
	                                              UGameplayStatics::GetWorldDeltaSeconds(this), TurretInterpSpeed));
}

void ABasePawn::Fire()
{
	if (ProjectileSpawnPoint != nullptr)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
		                                    ProjectileSpawnPoint->GetComponentRotation());

		Projectile->SetOwner(this);

		DrawDebugSphere(GetWorld(), ProjectileSpawnPoint->GetComponentLocation(), 10, 32, FColor::Blue, false, 3.0f);
	}
}
