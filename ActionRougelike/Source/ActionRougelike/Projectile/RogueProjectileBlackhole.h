// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectileBlackhole.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ARogueProjectileBlackhole : public ARogueProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueProjectileBlackhole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
