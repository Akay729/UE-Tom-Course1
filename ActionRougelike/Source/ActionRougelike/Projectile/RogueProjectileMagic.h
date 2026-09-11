// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileMagic.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;

//Abstract impedisce di selezionare direttamente la classe dai dropwdown dei blueprint
UCLASS(Abstract)
class ACTIONROUGELIKE_API ARogueProjectileMagic : public AActor
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
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	//Effetto quando fa collisione con qualcosa
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const
	                FHitResult& Hit);
	
public:
	
	virtual void PostInitializeComponents() override;
	// Sets default values for this actor's properties
	ARogueProjectileMagic();
};


//Sono stati rimossi  beginplay e tick perchè attualmente non servono