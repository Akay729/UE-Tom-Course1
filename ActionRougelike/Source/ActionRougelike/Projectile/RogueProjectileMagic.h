// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileMagic.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UAudioComponent;

//Abstract impedisce di selezionare direttamente la classe dai dropwdown dei blueprint
UCLASS(Abstract)
class ACTIONROUGELIKE_API ARogueProjectileMagic : public ARogueProjectile
{
	GENERATED_BODY()

protected:
	
	// Damage viene tradotto in "Danno"... Ho perso 10 min per questo
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DmgTypeClass;

public:
	
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const
					FHitResult& Hit) override;

	ARogueProjectileMagic();
};

//Sono stati rimossi  beginplay e tick perchè attualmente non servono