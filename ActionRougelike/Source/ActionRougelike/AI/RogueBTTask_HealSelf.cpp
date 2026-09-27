// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTTask_HealSelf.h"

#include "AIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"

EBTNodeResult::Type URogueBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn * AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	check(AIPawn);
	
	URogueActionSystemComponent* ActionComp = AIPawn->GetComponentByClass<URogueActionSystemComponent>();
	if (ensure(ActionComp))
	{
		ActionComp->ApplayHealthChange(HealAmount);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
