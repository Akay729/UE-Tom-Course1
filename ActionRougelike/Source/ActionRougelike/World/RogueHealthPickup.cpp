// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueHealthPickup.h"

#include "NiagaraComponent.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RoguePlayerCharacter.h"


// Sets default values
ARogueHealthPickup::ARogueHealthPickup()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(50.f);
	RootComponent = SphereComponent;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(SphereComponent);
	
	PickupSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupNiagaraComponent"));
	PickupSystem->SetupAttachment(SphereComponent);
	
	bIsPickedUp = false;
}

void ARogueHealthPickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueHealthPickup::PickUpItem);
}


void ARogueHealthPickup::PickUpItem( UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)|| bIsPickedUp)
	{
		return;
	}
	
	URogueActionSystemComponent* OtherActorActionComp=  OtherActor->GetComponentByClass<URogueActionSystemComponent>();
	if (!OtherActorActionComp)
	{
		return;
	}
	
	OtherActorActionComp->ApplayHealthChange(50.f);
	UGameplayStatics::PlaySound2D(this, PickupSound);
	bIsPickedUp = true;
	Destroy();
	
}
