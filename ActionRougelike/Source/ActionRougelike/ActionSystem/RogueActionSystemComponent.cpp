// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"




// Sets default values for this component's properties
URogueActionSystemComponent::URogueActionSystemComponent()
{

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

bool URogueActionSystemComponent::IsFullHealth() const
{
	return FMath::IsNearlyEqual(RogueAttributeSet.Health, RogueAttributeSet.MaxHealth);
}
