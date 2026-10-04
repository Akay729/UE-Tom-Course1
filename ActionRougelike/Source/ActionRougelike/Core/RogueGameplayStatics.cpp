// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueGameplayStatics.h"

#include "RogueGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"


bool URogueGameplayStatics::IsFullHealth(URogueActionSystemComponent* ActionSystemComponent)
{
	FRogueAttribute* AttributeHealth = ActionSystemComponent->GetAttribute(RogueGameplayTags::Attribute_Health);
	FRogueAttribute* AttributeHealthMax = ActionSystemComponent->GetAttribute(RogueGameplayTags::Attribute_HealthMax);

	return FMath::IsNearlyEqual(AttributeHealth->GetValue(), AttributeHealthMax->GetValue());
}
