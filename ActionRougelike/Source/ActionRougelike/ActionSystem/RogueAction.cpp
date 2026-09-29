// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction.h"

#include "RogueActionSystemComponent.h"

void URogueAction::StartAction_Implementation()
{
	float GameTime = GetWorld()->TimeSeconds;
	
	//I 2 Log fanno la stessa cosa
	
	UE_LOGFMT(LogTemp, Log, "STARTED ACTION: {ActionName} - {WorldTime}", ActionName, GameTime);
	//UE_LOGFMT(LogTemp, Log, "STARTED ACTION {ActionName} - {WorldTime}", 
	//	("ActionName", ActionName), 
	//	("WorldTime",GameTime));
}

void URogueAction::StopAction_Implementation()
{
	float GameTime = GetWorld()->TimeSeconds;
	
	//I 2 Log fanno la stessa cosa
	
	UE_LOGFMT(LogTemp, Log, "STOPPED ACTION: {ActionName} - {WorldTime}", ActionName, GameTime);
	//UE_LOGFMT(LogTemp, Log, "STARTED ACTION {ActionName} - {WorldTime}", 
	//	("ActionName", ActionName), 
	//	("WorldTime",GameTime));
}

URogueActionSystemComponent* URogueAction::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}


