// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RoguePlayerCharacter.generated.h"


class URogueActionSystemComponent;
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
	
	
	//Type of projectile
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TSubclassOf<ARogueProjectile> PrimaryAttackProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TSubclassOf<ARogueProjectile> SpecialProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TSubclassOf<ARogueProjectile> SecondaryAttackProjectileClass;
	
	// -- aniamtion and effects 
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TObjectPtr<UAnimMontage> AttackMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	TObjectPtr<UAnimMontage> DeathMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TObjectPtr<UNiagaraSystem> CastingEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack")
	TObjectPtr<USoundBase> ChargeSoundEffect;
	
	// -- components --
	// Vecchia alternativa non si usa più: 
	// UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<URogueActionSystemComponent> ActionSystemComponent ;
	
	
	// -- input --
	//Ho dovuto includere in questa maniere il MappingContext perchè dal project setting non andava
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Look;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_PrimaryAttack;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Jump;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_AbilityTeleport;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_AbilityBlackhole;
	
	// -- function
	void MoveAction(const FInputActionValue& value);
	
	void LookAction(const FInputActionInstance& value);
	
	void StartProjectileAttack(TSubclassOf<ARogueProjectile> ProjectileClass);
	void AttackTimerEnlapsed(TSubclassOf<ARogueProjectile> ProjectileClass);

	UFUNCTION()
	void OnHealthChanged(float NewHealth, float OldHealth);
	
public:
	
	
	virtual void PostInitializeComponents() override; 
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

};
