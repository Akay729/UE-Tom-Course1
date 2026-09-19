// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectile.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARogueProjectile::ARogueProjectile()
{
	// Creato un component per la collisione in questo caso sui usa sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetSphereRadius(16.f);
	SphereComponent->SetCollisionProfileName("Projectile");
	RootComponent = SphereComponent;
	
	// Creato un component niagara per aggiungere un VFX al proittile
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);
	
	// Creato un component audio per aggiungere un SFX al proittile
	LoopedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedAudioComponent"));
	LoopedAudioComponent->SetupAttachment(SphereComponent);
	
	//Creato un component per Movement di base del proittile 
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
}

void ARogueProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &ARogueProjectile::OnActorHit);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	PlayHitEffects();
	Destroy();
}

void ARogueProjectile::PlayHitEffects()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, HitNiagaraSystem, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, HitSoundBase, GetActorLocation());
}
