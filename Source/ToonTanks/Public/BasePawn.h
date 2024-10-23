// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
private:
	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> TurretMesh;
	UPROPERTY(VisibleAnywhere,meta = (AllowPrivateAccess=true))
	TObjectPtr<USceneComponent> ProjectileSpawnPoint;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
