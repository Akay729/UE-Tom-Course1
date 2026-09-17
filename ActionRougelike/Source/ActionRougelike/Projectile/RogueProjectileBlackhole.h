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
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Componets")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Blackhole")
	float GravityRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Blackhole")
	float ActionRadius = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Blackhole")
	float Duration = 5.f;
	
public:
	
	UFUNCTION()
	void DestroyBlackhole();
	
	virtual void Tick(float DeltaTime) override;
	
	ARogueProjectileBlackhole();
};
