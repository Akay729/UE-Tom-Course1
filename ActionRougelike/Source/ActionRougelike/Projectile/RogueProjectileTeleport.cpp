// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileTeleport.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARogueProjectileTeleport::ARogueProjectileTeleport()
{
	bIsExploding = false;
}

void ARogueProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	PawnToTeleport = GetInstigator();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ARogueProjectileTeleport::StartTeleport,
		timeBeforeTeleport, false);
}

void ARogueProjectileTeleport::StartTeleport()
{
	if (bIsExploding ||GetWorldTimerManager().TimerExists(TeleportTimerHandle))
	{
		Destroy();
		return;
	}
	if (!IsValid(PawnToTeleport))
	{
		Destroy();
		return;
	}
	
	LoopedNiagaraComponent->Deactivate();
	LoopedAudioComponent->Stop();
	
	//Effects
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, StartPointTeleportSystem, PawnToTeleport->GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, StartPointTeleportSound, PawnToTeleport->GetActorLocation());
	
	GetWorldTimerManager().SetTimer(TeleportTimerHandle, this, &ARogueProjectileTeleport::Teleport,
		teleportTimeDistance, false);
}

void ARogueProjectileTeleport::Teleport()
{
	bIsExploding = true;
	if (!IsValid(PawnToTeleport))
	{
		Destroy();
		return;
	}
	
	//PlayhitEffects in questo caso è il varoco finale del teleport
	PlayHitEffects();
	
	PawnToTeleport->TeleportTo(GetActorLocation(), PawnToTeleport->GetActorRotation());
	Destroy();
}

void ARogueProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	StartTeleport();
	
}

