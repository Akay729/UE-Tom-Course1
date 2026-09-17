// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileBlackhole.h"

#include "Components/SphereComponent.h"
#include "Engine/OverlapResult.h"
#include "PhysicsEngine/RadialForceComponent.h"


ARogueProjectileBlackhole::ARogueProjectileBlackhole()
{
	//PrimaryActorTick.bCanEverTick = true;
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->ImpulseStrength = -1000000;
	RadialForceComponent->ForceStrength = -1000000;
	RadialForceComponent->Radius = GravityRadius;
	RadialForceComponent->bIgnoreOwningActor = true;
	//RadialForceComponent->AddCollisionChannelToAffect(ECC_GameTraceChannel1);
	
}

void ARogueProjectileBlackhole::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	
	FTimerHandle BlackholeTimerHandle;
	GetWorldTimerManager().SetTimer(BlackholeTimerHandle ,this,  &ARogueProjectileBlackhole::DestroyBlackhole, Duration);
}

void ARogueProjectileBlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RadialForceComponent->FireImpulse();
	
	TArray<FOverlapResult> OverlapResults;
	
	FCollisionObjectQueryParams CollisonObjectParams;
	CollisonObjectParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(ActionRadius);
	
	GetWorld()->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), FQuat::Identity, CollisonObjectParams, CollisionShape);
	DrawDebugSphere(GetWorld(), GetActorLocation(),ActionRadius, 32, FColor::Red, false, 0.1f);
	
	for (FOverlapResult& OverlapResult : OverlapResults)
	{
		AActor* ResultActor = OverlapResult.GetActor();
		if (IsValid(ResultActor))
		{
			ResultActor->Destroy();
		}
	}
}

void ARogueProjectileBlackhole::DestroyBlackhole()
{
	Destroy();
}
