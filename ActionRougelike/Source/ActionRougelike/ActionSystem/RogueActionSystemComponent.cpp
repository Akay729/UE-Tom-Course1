// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"

#include "RogueAction.h"


// Sets default values for this component's properties
URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	for (TSubclassOf<URogueAction> Action : DefaultActions)
	{
		if (ensure(Action))
		{
			GrantAction(Action);
		}
	}
	
}

void URogueActionSystemComponent::GrantAction(TSubclassOf<URogueAction> NewActionClass)
{
	URogueAction* NewAction = NewObject<URogueAction>(this, NewActionClass);
	Actions.Add(NewAction);
}

void URogueActionSystemComponent::StartAction(FName InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StartAction();
			return;
		}
		
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Action %s not found"), *InActionName.ToString());
}

void URogueActionSystemComponent::StopAction(FName InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
		
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Action %s not found"), *InActionName.ToString());
}


void URogueActionSystemComponent::ApplayHealthChange(float InValueChange)
{
	float OldHealth = RogueAttributeSet.Health ;
	
	RogueAttributeSet.Health = FMath::Clamp(RogueAttributeSet.Health + InValueChange, 0.0f, RogueAttributeSet.MaxHealth );
	
	if (!FMath::IsNearlyEqual(OldHealth, RogueAttributeSet.Health))
	{
		OnHealthChanged.Broadcast(RogueAttributeSet.Health, OldHealth);
	}
	UE_LOG(LogTemp, Log, TEXT("New Health: %f Max Health %f"), RogueAttributeSet.Health, RogueAttributeSet.MaxHealth);
}

float URogueActionSystemComponent::GetCurrentHealth()
{
	return RogueAttributeSet.Health;
}

float URogueActionSystemComponent::GetMaxHealth()
{
	return RogueAttributeSet.MaxHealth;
}

bool URogueActionSystemComponent::IsFullHealth() const
{
	return FMath::IsNearlyEqual(RogueAttributeSet.Health, RogueAttributeSet.MaxHealth);
}



