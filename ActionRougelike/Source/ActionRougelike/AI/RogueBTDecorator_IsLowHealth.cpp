// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTDecorator_IsLowHealth.h"

#include "AIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"

bool URogueBTDecorator_IsLowHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	check(AIPawn);
	
	URogueActionSystemComponent* ActionComp = AIPawn->GetComponentByClass<URogueActionSystemComponent>();
	
	if (ensure(ActionComp))
	{
		check(false);
		return true; //(ActionComp->GetCurrentHealth() / ActionComp->GetMaxHealth()) < LowHealthFraction;
	}
	return false;
}