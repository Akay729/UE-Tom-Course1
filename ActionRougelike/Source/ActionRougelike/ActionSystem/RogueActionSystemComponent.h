// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"


struct FRogueAttributeSet
{
	FRogueAttributeSet() 
		: Health(100.f) {}
	float Health;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void ApplayHealthChange(float InValueChange);
	
protected:
	FRogueAttributeSet RogueAttributeSet;
	
public:

	URogueActionSystemComponent();
	
};
