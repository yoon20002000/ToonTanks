// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 200.0f;
	UPROPERTY(EditAnywhere)
	float TurnRate = 45.0f;
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerControllerRef;
public:
	ATank();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	void Move(float InValue);
	void Turn(float InValue);
	
};
