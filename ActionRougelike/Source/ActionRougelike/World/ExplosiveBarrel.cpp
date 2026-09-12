// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetSimulatePhysics(true);
	RootComponent = StaticMeshComponent;
	
	bIsExploding = false;
	
	//@todo URadialForceComponent
	
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(StaticMeshComponent);
	
	RadialForceComponent->Radius = 750.f;
	RadialForceComponent->ImpulseStrength = 150000.f;
	RadialForceComponent->ForceStrength = 1000.f;
	RadialForceComponent->Falloff = ERadialImpulseFalloff::RIF_Linear;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;
	
	
	
	/*//Component per sfx esplosione
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(StaticMeshComponent);
	
	//Component per vfx esplosione
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(StaticMeshComponent);*/
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
	if(!bIsExploding)
	{
		bIsExploding = true;
		FTimerHandle TimerHandle;
		constexpr float ExplosionDelayTime = 3.f;
		GetWorldTimerManager().SetTimer(TimerHandle,this, &AExplosiveBarrel::Explode,ExplosionDelayTime,false);
		
		FVector SocketLocation = StaticMeshComponent->GetSocketLocation(SocketName);
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionTriggerSound, SocketLocation);
		
	}
	
	// Questa ho dovuto guardare non 
	UNiagaraFunctionLibrary::SpawnSystemAttached(ExplosionTriggerSystem, StaticMeshComponent, NAME_None, 
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AExplosiveBarrel::Explode()
{
	FVector SocketLocation = StaticMeshComponent->GetSocketLocation(SocketName);	
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionAudio, SocketLocation);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionSystem, SocketLocation);
	RadialForceComponent->FireImpulse();
	Destroy();
	//@todo RadialExplosion
}


