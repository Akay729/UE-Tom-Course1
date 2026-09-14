// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionProfileName("PhysicsActor");
	StaticMeshComponent->SetCollisionProfileName("Interaction");
	RootComponent = StaticMeshComponent;
	
	bExploded = false;
	
	//@todo URadialForceComponent
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	
	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->ImpulseStrength = 150000.f;
	RadialForceComponent->ForceStrength = 1000.f;
	RadialForceComponent->Falloff = ERadialImpulseFalloff::RIF_Linear;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = false; //it's fly now!
	
}

/*void AExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnHit);
}*/

float AExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	StartExplode();
	return ActualDamage;
}

void AExplosiveBarrel::Interact()
{
	StartExplode();
}

void AExplosiveBarrel::StartExplode()
{
	if(bExploded || GetWorldTimerManager().TimerExists(ExplosionTimerHandle))
	{
		return;
	}
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle,this, &AExplosiveBarrel::Explode,ExplosionDelayTime,false);
	
	ActiveBurningSoundComponent = UGameplayStatics::SpawnSoundAttached(ExplosionTriggerSound, StaticMeshComponent);
	
	// Questa ho dovuto guardare non sapevo
	ActiveBurningEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionTriggerSystem,
		StaticMeshComponent, NAME_None,FVector::ZeroVector, FRotator::ZeroRotator,
		EAttachLocation::Type::SnapToTarget, true);
}

void AExplosiveBarrel::Explode()
{
	ActiveBurningSoundComponent->Stop();
	ActiveBurningEffectComponent->Deactivate();
	
	FVector SocketLocation = StaticMeshComponent->GetSocketLocation(SocketName);	
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionAudio, SocketLocation);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionSystem, SocketLocation);
	RadialForceComponent->FireImpulse();
	bExploded = true;
	//Destroy();
}
