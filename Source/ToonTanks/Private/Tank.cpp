// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent != nullptr)
	{
		PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
		PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
		PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TankPlayerController != nullptr)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		if (HitResult.IsValidBlockingHit())
		{
			DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20, 30, FColor::Red);
			RotateTurret(HitResult.ImpactPoint);
		}
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}


void ATank::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float InValue)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	FVector DeltaLocation;
	DeltaLocation.X = InValue * MoveSpeed * DeltaTime;

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float InValue)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = InValue * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}
