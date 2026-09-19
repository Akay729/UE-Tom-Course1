// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"




// Sets default values for this component's properties
URogueActionSystemComponent::URogueActionSystemComponent()
{

}

void URogueActionSystemComponent::ApplayHealthChange(float InValueChange)
{
	RogueAttributeSet.Health += InValueChange;
	UE_LOG(LogTemp, Log, TEXT("New Health: %f"), RogueAttributeSet.Health);
}