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
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor>  OwnerActor;
	
	UPROPERTY(EditAnywhere, Category = "Teleport")
	float teleportSpeed = 0.2f;
	
	UPROPERTY(EditAnywhere, Category = "Teleport")
	float teleportTimeDistance = 0.2f; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	TObjectPtr<USoundBase>  StartPointTeleportSound;
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	TObjectPtr<USoundBase>  EndPointTeleportSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	TObjectPtr<UNiagaraSystem>  StartPointTeleportSystem;
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	TObjectPtr<UNiagaraSystem>  EndTeleportSystem;
	
	UPROPERTY(VisibleAnywhere)
	bool bIsExploding;
	
	UPROPERTY(VisibleAnywhere)
	APawn* PawnToTeleport;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	
	void StartExplosion();
	void Teleport();
	// Sets default values for this actor's properties
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	ARogueProjectileTeleport();
};
