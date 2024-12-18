// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsInFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}	
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Fire()
{
	Super::Fire();
}

void ATower::CheckFireCondition()
{
	if(IsInFireRange())
	{
		Fire();
	}
}

bool ATower::IsInFireRange() const
{
	if(Tank == nullptr && Tank->GetIsAlive() == false)
	{
		return false;
	}
	const FVector Location = GetActorLocation();
	const FVector TargetLocation = Tank->GetActorLocation();
	const float Distance = FVector::Dist(Location, TargetLocation); 
	return Distance <= SearchingDistance;
}
