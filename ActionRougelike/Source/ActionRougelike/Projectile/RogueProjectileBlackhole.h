// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectileBlackhole.generated.h"

class URadialForceComponent;

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARogueProjectileBlackhole : public ARogueProjectile
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Componets")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Blackhole")
	float GravityRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Blackhole")
	float LifeSpan = 5.f;
	
public:
	
	virtual void PostInitializeComponents() override; 
	
	UFUNCTION()
	void OnSphereOverlappedActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	ARogueProjectileBlackhole();
};
