// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePickupActor.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ARoguePickupActor::ARoguePickupActor()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(PickupRadius);
	SphereComponent->SetCollisionProfileName("Pickup");
	RootComponent = SphereComponent;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionProfileName("NoCollision");
	MeshComponent->SetupAttachment(SphereComponent);
	
	PickupSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupNiagaraComponent"));
	PickupSystem->SetupAttachment(SphereComponent);
	
	bIsPickedUp = false;
}

void ARoguePickupActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARoguePickupActor::OnActorOverlapped);
}

void ARoguePickupActor::OnActorOverlapped( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
