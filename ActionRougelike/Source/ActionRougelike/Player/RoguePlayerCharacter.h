// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoguePlayerCharacter.generated.h"


class ARogueProjectile;
class UNiagaraSystem;
struct FInputActionInstance;
struct FInputActionValue;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class ARogueProjectileMagic;

UCLASS()
class ACTIONROUGELIKE_API ARoguePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoguePlayerCharacter();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	FName MuzzleSocketName;
	
	//Type of projectile
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TSubclassOf<ARogueProjectile> PrimaryAttackProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TSubclassOf<ARogueProjectile> SpecialProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TSubclassOf<ARogueProjectile> SecondaryAttackProjectileClass;
	//---
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TObjectPtr<USoundBase> ChargeSoundEffect;
	
	// Vecchia alternativa non si usa più: 
	// UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;
	
	// -- Ability --
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_AbilityTeleport;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_AbilityBlackhole;
	
	//Ho dovuto includere in questa maniere il MappingContext perchè dal project setting non andava
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* DefaultMappingContext;

	void MoveAction(const FInputActionValue& value);
	
	void LookAction(const FInputActionInstance& value);
	
	void StartProjectileAttack(TSubclassOf<ARogueProjectile> ProjectileClass);
	void AttackTimerEnlapsed(TSubclassOf<ARogueProjectile> ProjectileClass);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
