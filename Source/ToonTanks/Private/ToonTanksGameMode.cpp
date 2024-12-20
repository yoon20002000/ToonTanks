// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController != nullptr)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* Tower = Cast<ATower>(DeadActor); Tower != nullptr)
	{
		Tower->HandleDestruction();
		--TargetTowers;
		if(TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if(ToonTanksPlayerController != nullptr)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableTimerHandle ;
		const FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,
		                                                                   &AToonTanksPlayerController::SetPlayerEnabledState,
		                                                                   true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, InputDelegate, StartDelay, false);
	}
}

int32 AToonTanksGameMode::GetTargetTowerCount() const
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),OutActors);

	return OutActors.Num();
}
