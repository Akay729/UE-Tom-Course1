// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueProjectileTeleport.generated.h"

class UNiagaraSystem;

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARogueProjectileTeleport : public ARogueProjectile
{
	GENERATED_BODY()

protected:
	FTimerHandle SpawnTimerHandle;
	FTimerHandle TeleportTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float timeBeforeTeleport = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float teleportTimeDistance = 0.2f; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport Effect")
	TObjectPtr<USoundBase>  StartPointTeleportSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport Effect")
	TObjectPtr<UNiagaraSystem>  StartPointTeleportSystem;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsExploding;
	
	UPROPERTY(VisibleAnywhere)
	APawn* PawnToTeleport;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	
	void StartTeleport();
	void Teleport();
	// Sets default values for this actor's properties
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	ARogueProjectileTeleport();
};
