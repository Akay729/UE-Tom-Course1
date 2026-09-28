// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueAction.h"
#include "RogueAction_ProjectileAttack.generated.h"

class ARogueProjectile;
class UNiagaraSystem;
class USoundBase;
/**
 * 
 */
UCLASS(Abstract)
class ACTIONROUGELIKE_API URogueAction_ProjectileAttack : public URogueAction
{
	GENERATED_BODY()
	
public:
	virtual void StartAction() override;

	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Attack")
	TSubclassOf<ARogueProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Attack")
	FName MuzzleSocketName =  FName("Muzzle_01");
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Attack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Attack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile Attack")
	TObjectPtr<USoundBase> ChargeSoundEffect;
	
	void AttackTimerEnlapsed();
	
public:
	
	URogueAction_ProjectileAttack();
};
