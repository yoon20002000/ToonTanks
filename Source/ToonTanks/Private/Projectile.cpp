// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
	RootComponent = MeshComp;
	ProjectileMovementCmp = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementCmp->MaxSpeed = 1300.f;
	ProjectileMovementCmp->InitialSpeed = 1300.f;

	ParticleSystemCmp = CreateDefaultSubobject<UParticleSystemComponent>("Particle System Component");
	ParticleSystemCmp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	MeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	ensure(HitParticles);
	ensure(LaunchSound);
	ensure(HitSound);

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ThisOwner = GetOwner();

	if (ThisOwner == nullptr)
	{
		Destroy();
		return;
	}
	AController* OwnerInstigator = ThisOwner->GetInstigatorController();
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor != nullptr && OtherActor != this && OtherActor != ThisOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerInstigator, this, DamageTypeClass);
		UE_LOG(LogTemp, Log, TEXT(" Hit Comp : %s, Other Hit Actor : %s, Other Comp : %s"), *HitComponent->GetName(),
		       *OtherActor->GetName(), *OtherComp->GetName());

		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
	}
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
	Destroy();
}
