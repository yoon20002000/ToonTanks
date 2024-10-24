// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Tank != nullptr)
	{
		const FVector Location = GetActorLocation();
		const FVector TargetLocation = Tank->GetActorLocation();
		if(const float Distance = FVector::Dist(Location, TargetLocation); Distance <= SearchingDistance)
		{
			RotateTurret(TargetLocation);
		}	
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
