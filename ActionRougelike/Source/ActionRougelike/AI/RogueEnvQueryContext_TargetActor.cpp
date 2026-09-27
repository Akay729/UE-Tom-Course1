// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueEnvQueryContext_TargetActor.h"

#include "AIController.h"
#include "RogueGameTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void URogueEnvQueryContext_TargetActor::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	APawn* QuerierPawn = Cast<APawn>(QueryInstance.Owner.Get());
	if (!QuerierPawn)
	{
		return;
	}

	AAIController* Controller = Cast<AAIController>(QuerierPawn->GetController());
	if (!Controller)
	{
		return;
	}

	UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();
	if (!Blackboard)
	{
		return;
	}

	AActor* TargetActor = Cast<AActor>(Blackboard->GetValueAsObject(Name_TargetActor));
	if (!TargetActor)
	{
		return;
	}

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, TargetActor);
}
