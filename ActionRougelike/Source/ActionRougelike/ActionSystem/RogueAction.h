// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

class URogueActionSystemComponent;
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ACTIONROUGELIKE_API URogueAction : public UObject
{
	GENERATED_BODY()

protected:
	
	/*
	 * Avendo implementatto FGameplayTag ora sarà possibile sceglire attraverso un menu
	 * a tendina nel editor che mostrerà le varie opzioni gameplaty tag
	 * 
	 * (Bisogna includere GameplayTag nel build.cs)
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FGameplayTag ActionName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FGameplayTagContainer GrantedTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FGameplayTagContainer BlockedTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	float CooldownTime = 0.f;
	
public:
	
	UFUNCTION(BlueprintCallable)
	URogueActionSystemComponent* GetOwningComponent() const;
	
	bool CanStart() const;
	
	bool IsRunning() const
	{
		return bIsRunning;
	};
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StartAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StopAction(); 
	
	float GetCooldownTimeRemaining() const;
	
	FGameplayTag GetActionName() const
	{
		return ActionName;
	}
	
protected:
	
	// GameTime necessario a finche l'azione è nuovamente disponibile.
	UPROPERTY(Transient)
	float CooldownUntil = 0.f;
	
	UPROPERTY(Transient)
	bool bIsRunning = false;
};
