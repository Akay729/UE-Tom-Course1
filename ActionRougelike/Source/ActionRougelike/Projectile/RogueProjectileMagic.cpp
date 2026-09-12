// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileMagic.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


ARogueProjectileMagic::ARogueProjectileMagic()
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


void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &ARogueProjectileMagic::OnActorHit);
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit )
{
	
	FVector DirectionHit =  GetActorRotation().Vector();
	
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, DirectionHit, Hit, GetInstigatorController(),
		this, DmgTypeClass);
	
	//UGameplayStatics::ApplyDamage(OtherActor, 10.f, GetInstigatorController(), this, DmgTypeClass);
	
	/* Qua si poteva usare FHitResult.HitLocation per una cordinata migliore al posto di GetActorLocation()
	 * Dato che il primo da la cordinata della collisione ed il secondo quella del attore in question (il proittile) 
	*/
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	
	UGameplayStatics::PlaySoundAtLocation(this, HitSoundEffect, GetActorLocation(),FRotator::ZeroRotator);
	Destroy();
}

