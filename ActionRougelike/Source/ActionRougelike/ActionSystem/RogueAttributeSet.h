// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAttributeSet.generated.h"


class URogueActionSystemComponent;

USTRUCT()
struct FRogueAttribute
{
	GENERATED_BODY()
	
	FRogueAttribute(){}
	
	FRogueAttribute(float InBase): Base(InBase){}
	
	UPROPERTY(EditAnywhere)
	float Base = 0.0f;
	
	UPROPERTY(Transient)
	float Modifier = 0.0f;
	
	float GetValue()
	{
		return Base+Modifier;
	}
	
};

/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API URogueAttributeSet : public UObject
{
	GENERATED_BODY()
	
public:
	
	URogueActionSystemComponent* GetOwningComponent() const;
	
	virtual void InitializeAttributes() {};
	
	virtual void PostAttributeChanged() {};
	
};


UCLASS()
class URogueHealthAttributeSet : public URogueAttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, Category=Attribute)
	FRogueAttribute Health;

	UPROPERTY(EditAnywhere, Category=Attribute)
	FRogueAttribute HealthMax;
	
	virtual void PostAttributeChanged() override;
	
	URogueHealthAttributeSet();
};

UCLASS()
class URoguePawnAttributeSet : public URogueHealthAttributeSet
{
	GENERATED_BODY()

public:
	
	virtual void InitializeAttributes() override;
	
	virtual void PostAttributeChanged() override;
	
	void ApplyMoveSpeed();
	
	
	/*
	 * Walking Speed on linked on CharacterMovementComponent
	 */
	UPROPERTY(EditAnywhere, Category=Attribute)
	FRogueAttribute MovementSpeed;
	
	URoguePawnAttributeSet();
};


UCLASS()
class URoguePlayerAttributeSet : public URoguePawnAttributeSet
{
	GENERATED_BODY()

public:
};


UCLASS()
class URogueMonsterAttributeSet : public URoguePawnAttributeSet
{
	GENERATED_BODY()

public:
	
	URogueMonsterAttributeSet();
};