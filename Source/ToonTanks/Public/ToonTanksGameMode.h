// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
private :
	TObjectPtr<class ATank> Tank;
	TObjectPtr<class AToonTanksPlayerController> ToonTanksPlayerController;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	float StartDelay = 3.0f;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	int32 TargetTowers = 0;
public:
	void ActorDied(AActor* DeadActor);
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bIsWonGame);
private:
	void HandleGameStart();
	int32 GetTargetTowerCount() const;
};
