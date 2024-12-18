// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
private:
	TObjectPtr<ATank> Tank;
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	float SearchingDistance = 500.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
protected:
	virtual void BeginPlay() override;
	virtual void Fire() override;
private:
	void CheckFireCondition();
	bool IsInFireRange() const;
};
