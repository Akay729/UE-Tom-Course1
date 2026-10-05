// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RogueAttributeSet.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAttributeSet;
class URogueAction;

UENUM(BlueprintType)
enum EAttributeModifyType
{
	Base,
	Modifier,
	OverrideBase,
	Invalid
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayTag /*AttributeTag*/, float /*NewAttributeValue*/, float /*OldAttributeValue*/);


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
	
	UFUNCTION(BlueprintCallable)
	void ApplayAttributeChange(FGameplayTag AttributeTag, float Delta,  EAttributeModifyType ModifyType = Base);
	
	/*
	 *This function is made with the intent to  compare attribute that have a MaxAttribute
	 *Example:
	 *Stamina -> StaminaMax
	 *Health -> HealthMax
	 */ 
	bool IsAttributeFull(FGameplayTag InAttributeTag, FGameplayTag AttributeMaxTag);
	
	FOnAttributeChanged& GetAttributeListener(FGameplayTag InAttributeTag);
	
	FRogueAttribute* GetAttribute(FGameplayTag InAttributeTag); 
		
	virtual void InitializeComponent() override;
	
	FGameplayTagContainer ActiveGameplayTags;
	
	FGameplayTagContainer BlockedGameplayTags;
	
protected:
	
	UPROPERTY()
	TObjectPtr<URogueAttributeSet> RogueAttributeSet;
	
	TMap<FGameplayTag, FRogueAttribute*> CachedAttributes;
	
	UPROPERTY(EditAnywhere, Category=Attributes, NoClear)
	TSubclassOf<URogueAttributeSet> RogueAttributeSetClass;
	
	TMap<FGameplayTag, FOnAttributeChanged> AttributeListeners;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
	
public:
	
	virtual void BeginPlay() override;
	
	URogueActionSystemComponent();
	
};
