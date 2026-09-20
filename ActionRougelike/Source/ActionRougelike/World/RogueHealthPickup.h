// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueHealthPickup.generated.h"

class UNiagaraComponent;
class USphereComponent;

UCLASS()
class ACTIONROUGELIKE_API ARogueHealthPickup : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> PickupSystem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<USoundBase> PickupSound;

	UFUNCTION()
	void PickUpItem( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	bool bIsPickedUp;
	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	float HealhValue;
	
public:
	
	virtual void PostInitializeComponents() override;
	// Sets default values for this actor's properties
	ARogueHealthPickup();
};