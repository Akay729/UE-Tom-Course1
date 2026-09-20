// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoguePickupActor.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARoguePickupActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> PickupSystem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	TObjectPtr<USoundBase> PickupSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pickup")
	float PickupRadius;
	
	bool bIsPickedUp;
	
	UFUNCTION()
	virtual void OnActorOverlapped( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void PostInitializeComponents() override;
	ARoguePickupActor();
};
