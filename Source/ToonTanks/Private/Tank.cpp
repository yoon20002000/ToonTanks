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

	if(PlayerInputComponent != nullptr)
	{
		PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Move(float InValue)
{
	const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	FVector DeltaLocation;
	DeltaLocation.X = InValue* MoveSpeed * DeltaTime;

	AddActorLocalOffset(DeltaLocation);
}
