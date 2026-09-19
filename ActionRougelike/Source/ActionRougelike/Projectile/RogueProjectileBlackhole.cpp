// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileBlackhole.h"

#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"




ARogueProjectileBlackhole::ARogueProjectileBlackhole()
{
	//PrimaryActorTick.bCanEverTick = true;
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->ForceStrength = -1000000;
	RadialForceComponent->Radius = GravityRadius;
	RadialForceComponent->bIgnoreOwningActor = true;

	RadialForceComponent->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	InitialLifeSpan = LifeSpan;
	
}

void ARogueProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectileBlackhole::OnSphereOverlappedActor);
}

void ARogueProjectileBlackhole::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	const bool bSim = OtherComp->IsSimulatingPhysics();

	if (!bSim)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BH] Not destroyed (no SimulatePhysics): %s"), *OtherActor->GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[BH] DESTROY %s"), *OtherActor->GetName());
	OtherActor->Destroy();
}
