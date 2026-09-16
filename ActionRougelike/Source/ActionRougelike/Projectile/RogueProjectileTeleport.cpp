// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileTeleport.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARogueProjectileTeleport::ARogueProjectileTeleport()
{
	bIsExploding = false;
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ARogueProjectileTeleport::StartExplosion,teleportSpeed, false);
}

void ARogueProjectileTeleport::StartExplosion()
{
	if (bIsExploding ||GetWorldTimerManager().TimerExists(TeleportTimerHandle))
	{
		return;
	}
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ARogueProjectileTeleport::Teleport,teleportTimeDistance, false);
}

void ARogueProjectileTeleport::Teleport()
{
	FVector ProjectileLocation = GetActorLocation();
	APawn* PawnToTeleport = GetInstigator();
	if (!IsValid(PawnToTeleport))
	{
		Destroy();
		return;
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TeleportSystem, ProjectileLocation);
	UGameplayStatics::PlaySoundAtLocation(this, TeleportSound, ProjectileLocation);
	
	PawnToTeleport->TeleportTo(ProjectileLocation, PawnToTeleport->GetActorRotation());
	
	bIsExploding = true;
	Destroy();
}

void ARogueProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	StartExplosion();
	
}

