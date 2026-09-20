// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoguePickupActor.h"
#include "GameFramework/Actor.h"
#include "RogueHealthPickup.generated.h"

class UNiagaraComponent;
class USphereComponent;

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARogueHealthPickup : public ARoguePickupActor
{
	GENERATED_BODY()

protected:
	
	virtual void OnActorOverlapped( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	float HealingAmount;
	
public:
	
	// Sets default values for this actor's properties
	ARogueHealthPickup();
};