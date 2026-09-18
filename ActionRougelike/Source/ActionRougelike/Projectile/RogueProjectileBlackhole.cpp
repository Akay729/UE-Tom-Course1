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
	
	InitialLifeSpan = 5.0f;
	
}

void ARogueProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectileBlackhole::OnSphereOverlappedActor);
}

void ARogueProjectileBlackhole::OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("[BH] Overlap fired. Me=%s Other=%s Comp=%s"),
			*GetName(),
			OtherActor ? *OtherActor->GetName() : TEXT("NULL"),
			OtherComp ? *OtherComp->GetName() : TEXT("NULL"));

	if (!IsValid(OtherActor) || !IsValid(OtherComp))
	{
		UE_LOG(LogTemp, Error, TEXT("[BH] Abort: OtherActor or OtherComp invalid"));
		return;
	}
	

	const bool bSim = OtherComp->IsSimulatingPhysics();
	UE_LOG(LogTemp, Warning,
		TEXT("[BH] %s | Profile=%s ObjectType=%d CollisionEnabled=%d SimulatePhysics=%s"),
		*OtherActor->GetName(),
		*OtherComp->GetCollisionProfileName().ToString(),
		static_cast<int32>(OtherComp->GetCollisionObjectType()),
		static_cast<int32>(OtherComp->GetCollisionEnabled()),
		bSim ? TEXT("YES") : TEXT("NO"));

	if (!bSim)
	{
		UE_LOG(LogTemp, Warning, TEXT("[BH] Not destroyed (no SimulatePhysics): %s"), *OtherActor->GetName());
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[BH] DESTROY %s"), *OtherActor->GetName());
	OtherActor->Destroy();
}
