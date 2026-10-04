// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RogueAttributeSet.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAttributeSet;
class URogueAction;

UENUM()
enum EAttributeModifyType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid
};


// Dynamic: per esplorlo ai blueprint
// Multicast: per dirgli che si aspetta più listener
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	//Action
	void StartAction(FGameplayTag InActionName);
	
	void StopAction(FGameplayTag InActionName);
	
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);
	
	//Attributes
	
	void ApplayAttributeChange(FGameplayTag AttributeTag, float Delta,  EAttributeModifyType ModifyType = Base);
	
	/*
	 *This function is made with the intent to  compare attribute that have a MaxAttribute
	 *Example:
	 *Stamina -> StaminaMax
	 *Health -> HealthMax
	 */ 
	
	bool IsAttributeFull(FGameplayTag AttributeTag, FGameplayTag AttributeMaxTag);
	
	FRogueAttribute* GetAttribute(FGameplayTag InAttributeTag); 
	
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
		
	virtual void InitializeComponent() override;
	
	FGameplayTagContainer ActiveGameplayTags;
	
	FGameplayTagContainer BlockedGameplayTags;
	
protected:
	
	UPROPERTY()
	TObjectPtr<URogueAttributeSet> RogueAttributeSet;
	
	TMap<FGameplayTag, FRogueAttribute*> CachedAttributes;
	
	UPROPERTY(EditAnywhere, Category=Attributes, NoClear)
	TSubclassOf<URogueAttributeSet> RogueAttributeSetClass;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
	
public:

	URogueActionSystemComponent();
	
};
