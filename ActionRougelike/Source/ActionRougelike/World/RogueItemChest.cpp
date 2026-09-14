// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueItemChest.h"


// Sets default values
ARogueItemChest::ARogueItemChest()
{
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMeshComponent->SetCollisionProfileName("Interaction");
	RootComponent = BaseMeshComponent;
	
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComponent"));
	LidMeshComponent->SetCollisionProfileName("NoCollision");
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ARogueItemChest::Interact_Implementation()
{
	SetActorTickEnabled(true);
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentAnimationLidPitch = FMath::FInterpConstantTo(CurrentAnimationLidPitch, LidPitch, DeltaTime, InterpSpeed);
	LidMeshComponent->SetRelativeRotation(FRotator(CurrentAnimationLidPitch, 0.0f, 0.0f));
	
	if (FMath::IsNearlyEqual(CurrentAnimationLidPitch, LidPitch))
	{
		SetActorTickEnabled(false);
		ChestAnimationComplete();
	}
}

