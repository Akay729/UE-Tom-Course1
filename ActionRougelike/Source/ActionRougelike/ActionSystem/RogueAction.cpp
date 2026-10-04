// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction.h"

#include "RogueActionSystemComponent.h"

void URogueAction::StartAction_Implementation()
{
	bIsRunning = true;
	float GameTime = GetWorld()->TimeSeconds;
	
	//I 2 Log fanno la stessa cosa
	
	UE_LOGFMT(LogTemp, Log, "STARTED ACTION: {ActionName} - {WorldTime}", ActionName.GetTagName(), GameTime);
	
	//UE_LOGFMT(LogTemp, Log, "STARTED ACTION {ActionName} - {WorldTime}", 
	//	("ActionName", ActionName), 
	//	("WorldTime",GameTime));
	
	GetOwningComponent()->ActiveGameplayTags.AppendTags(GrantedTags);
}

void URogueAction::StopAction_Implementation()
{
	bIsRunning = false;
	float GameTime = GetWorld()->TimeSeconds;
	
	
	/*UE_LOGFMT(LogTemp, Log, "STOPPED ACTION: {ActionName} - {WorldTime}", ActionName, GameTime);*/
	
	UE_LOGFMT(LogTemp, Log, "STOPPED ACTION {ActionName} - {WorldTime}", 
		("ActionName", ActionName.ToString()), 
		("WorldTime", GameTime));
	
	CooldownUntil = GetWorld()->TimeSeconds + CooldownTime;
	
	GetOwningComponent()->ActiveGameplayTags.RemoveTags(GrantedTags);
}

bool URogueAction::CanStart() const
{
	if (IsRunning())
	{
		return false;
	}
	
	if (GetCooldownTimeRemaining() > 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("Time Remaining : %f "), GetCooldownTimeRemaining());
		return false;
	}

	if (GetOwningComponent()->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	
	
	return true;
}


float URogueAction::GetCooldownTimeRemaining() const
{
	return FMath::Max(0.f, CooldownUntil - GetWorld()->TimeSeconds);
}

URogueActionSystemComponent* URogueAction::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}




