// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectile.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UAudioComponent;

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARogueProjectile : public AActor
{
	GENERATED_BODY()

protected:
	/*
	 * Qui di seqguito venfo creati di puntatori a molteplici components
	 * Sphere per la collisione
	 * Niagara per l'effetto VFX
	 * ProjectileMovement per il movimento
	 * 
	 * Tutti componenti gia pre esistenti nel engine
	 */
	UPROPERTY(EditDefaultsOnly, Category="Projectile Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Projectile Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> ExplosionSound;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ExplosionSystem;

	UFUNCTION()
	void PlayExplodeEffects();
	
public:
	
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                FVector NormalImpulse, const FHitResult& Hit);
	// Sets default values for this actor's properties
	ARogueProjectile();	
};
