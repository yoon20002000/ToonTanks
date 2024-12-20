// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class AToonTanksGameMode;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	float MaxHealth = 100.f;
	float Health = 0.f;
	TObjectPtr<AToonTanksGameMode> ToonTanksGameMode;
public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public :
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

};
