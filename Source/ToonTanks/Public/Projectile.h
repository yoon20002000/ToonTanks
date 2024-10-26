// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> MeshComp;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementCmp;
	UPROPERTY(VisibleAnywhere, Category= "Combat")
	TObjectPtr<UParticleSystemComponent> ParticleSystemCmp;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 50.f;
	UPROPERTY(EditAnywhere, Category="Combat", meta=(AllowPrivateAccess=true))
	TObjectPtr<class UParticleSystem> HitParticles;

	UPROPERTY(EditAnywhere, Category="Combat", meta=(AllowPrivateAccess=true))
	TObjectPtr<class USoundBase> LaunchSound;
	UPROPERTY(EditAnywhere, Category="Combat", meta=(AllowPrivateAccess=true))
	TObjectPtr<class USoundBase> HitSound;
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
