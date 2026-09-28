// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAction;

USTRUCT(BlueprintType)
struct FRogueAttributeSet
{
	GENERATED_BODY();
	
	FRogueAttributeSet() 
		: Health(100.f), MaxHealth(100.f){}
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
	
	UPROPERTY(BlueprintReadOnly)
	float MaxHealth;
};

// Dynamic: per esplorlo ai blueprint
// Multicast: per dirgli che si aspetta più listener
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	void StartAction(FName InActionName);
	
	void ApplayHealthChange(float InValueChange);
	float GetCurrentHealth();
	float GetMaxHealth();
	bool IsFullHealth() const;
	
	virtual void InitializeComponent() override;
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);
protected:
	
	UPROPERTY(BlueprintReadOnly , Category = "Attributes")
	FRogueAttributeSet RogueAttributeSet;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
	
public:

	URogueActionSystemComponent();
	
};
