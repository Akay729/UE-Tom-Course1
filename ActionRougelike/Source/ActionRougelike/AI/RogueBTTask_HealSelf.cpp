// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTTask_HealSelf.h"

#include "AIController.h"
#include "RogueGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"

EBTNodeResult::Type URogueBTTask_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn * AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	check(AIPawn);
	
	URogueActionSystemComponent* ActionComp = AIPawn->GetComponentByClass<URogueActionSystemComponent>();
	if (ensure(ActionComp))
	{
		ActionComp->ApplayAttributeChange(RogueGameplayTags::Attribute_Health, HealAmount, Base);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
