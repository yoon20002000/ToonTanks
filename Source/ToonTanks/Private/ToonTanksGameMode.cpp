// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if(APlayerController* TankPlayerController = Tank->GetTankPlayerController(); TankPlayerController != nullptr)
		{
			Tank->DisableInput(TankPlayerController);
			TankPlayerController->bShowMouseCursor = false;
		}
	}
	else if (ATower* Tower = Cast<ATower>(DeadActor); Tower != nullptr)
	{
		Tower->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
}
