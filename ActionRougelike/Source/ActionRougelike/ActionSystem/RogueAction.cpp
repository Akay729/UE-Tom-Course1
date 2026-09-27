// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction.h"

void URogueAction::StartAction()
{
	float GameTime = 0.0f;
	
	//I 2 Log fanno la stessa cosa
	
	UE_LOGFMT(LogTemp, Log, "STARTED ACTION {ActionName} - {WorldTime}", ActionName, GameTime);
	//UE_LOGFMT(LogTemp, Log, "STARTED ACTION {ActionName} - {WorldTime}", 
	//	("ActionName", ActionName), 
	//	("WorldTime",GameTime));
}
