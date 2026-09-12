// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

class URadialForceComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class ACTIONROUGELIKE_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()

protected:
	
	//Component Staticmesh
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> ActiveBurningEffectComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UAudioComponent> ActiveBurningSoundComponent;
	
	//Effects variable
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TObjectPtr<USoundBase> ExplosionAudio;
	
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TObjectPtr<USoundBase> ExplosionTriggerSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	FName SocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TObjectPtr<UNiagaraSystem> ExplosionSystem;
	
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TObjectPtr<UNiagaraSystem> ExplosionTriggerSystem;
	
	UPROPERTY(VisibleAnywhere, Category = "Explosion")
	bool bExploded;
	
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float ExplosionDelayTime = 3.f;
	
	FTimerHandle ExplosionTimerHandle;
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();
	
	//virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION()
	void Explode();
};
