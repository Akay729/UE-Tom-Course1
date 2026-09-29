// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FName ActionName;
	
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
	
	FName GetActionName() const
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
