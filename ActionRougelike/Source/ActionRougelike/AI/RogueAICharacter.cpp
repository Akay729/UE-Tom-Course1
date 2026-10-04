// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAICharacter.h"

#include "RogueGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"


// Sets default values
ARogueAICharacter::ARogueAICharacter()
{
	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComponent"));
}

void ARogueAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

float ARogueAICharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ActionSystemComponent->ApplayAttributeChange(RogueGameplayTags::Attribute_Health, -ActualDamage, Base);
	return ActualDamage;
}

