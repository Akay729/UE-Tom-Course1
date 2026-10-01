// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAttributeSet;
class URogueAction;

// Dynamic: per esplorlo ai blueprint
// Multicast: per dirgli che si aspetta più listener
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	//Action
	void StartAction(FGameplayTag InActionName);
	
	void StopAction(FGameplayTag InActionName);
	
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);
	
	//Health
	void ApplayHealthChange(float InValueChange);
	
	float GetCurrentHealth();
	
	float GetMaxHealth();
	
	bool IsFullHealth() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
		
	virtual void InitializeComponent() override;
	
	FGameplayTagContainer ActiveGameplayTags;
	
	FGameplayTagContainer BlockedGameplayTags;
	
protected:
	
	UPROPERTY()
	TObjectPtr<URogueAttributeSet> RogueAttributeSet;
	
	UPROPERTY(EditAnywhere, Category=Attributes, NoClear)
	TSubclassOf<URogueAttributeSet> RogueAttributeSetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
	
public:

	URogueActionSystemComponent();
	
};
