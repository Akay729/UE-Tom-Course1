// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileMagic.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UAudioComponent;

//Abstract impedisce di selezionare direttamente la classe dai dropwdown dei blueprint
UCLASS(Abstract)
class ACTIONROUGELIKE_API ARogueProjectileMagic : public AActor
{
	GENERATED_BODY()

protected:
	
	// Damage viene tradotto in "Danno"... Ho perso 10 min per questo
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DmgTypeClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<USoundBase> HitSoundEffect;
	
	//Effetto quando fa collisione con qualcosa
	UPROPERTY(EditAnywhere, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	/*
	 * Qui di seqguito venfo creati di puntatori a molteplici components
	 * Sphere per la collisione
	 * Niagara per l'effetto VFX
	 * ProjectileMovement per il movimento
	 * 
	 * Tutti componenti gia pre esistenti nel engine
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const
	                FHitResult& Hit);
	
public:
	
	virtual void PostInitializeComponents() override;
	// Sets default values for this actor's properties
	ARogueProjectileMagic();
};


//Sono stati rimossi  beginplay e tick perchè attualmente non servono