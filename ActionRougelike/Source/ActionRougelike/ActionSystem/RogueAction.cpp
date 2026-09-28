// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction.h"

#include "RogueActionSystemComponent.h"

void URogueAction::StartAction()
{
	double GameTime = GetWorld()->GetTimeSeconds();
	
	//I 2 Log fanno la stessa cosa
	
	UE_LOGFMT(LogTemp, Log, "STARTED ACTION {ActionName} - {WorldTime}", ActionName, GameTime);
	//UE_LOGFMT(LogTemp, Log, "STARTED ACTION {ActionName} - {WorldTime}", 
	//	("ActionName", ActionName), 
	//	("WorldTime",GameTime));
}

URogueActionSystemComponent* URogueAction::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}
