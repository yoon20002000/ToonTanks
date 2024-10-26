// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetPlayerEnabledState(const bool bIsPlayerEnabled)
{
	if(bIsPlayerEnabled == true)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bIsPlayerEnabled;
}
