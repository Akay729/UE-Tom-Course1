// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"
#include "RogueAttributeSet.h"
#include "RogueAction.h"
#include "RogueGameplayTags.h"


// Sets default values for this component's properties
URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;
	RogueAttributeSetClass = URogueAttributeSet::StaticClass();
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	RogueAttributeSet = NewObject<URogueAttributeSet>(this , RogueAttributeSetClass);
	
	for (TFieldIterator<FStructProperty> PropIt(RogueAttributeSet->GetClass()); PropIt; ++PropIt)
	{
		FRogueAttribute* FoundAttribute = PropIt->ContainerPtrToValuePtr<FRogueAttribute>(RogueAttributeSet);
		
		FName AttributeTagName = FName("Attribute."+ PropIt->GetName());
		FGameplayTag AttributeTag = FGameplayTag::RequestGameplayTag(AttributeTagName);
		
		CachedAttributes.Add(AttributeTag, FoundAttribute);
	}
	
	for (TSubclassOf<URogueAction> Action : DefaultActions)
	{
		if (ensure(Action))
		{
			GrantAction(Action);
		}
	}
	
}

void URogueActionSystemComponent::GrantAction(TSubclassOf<URogueAction> NewActionClass)
{
	URogueAction* NewAction = NewObject<URogueAction>(this, NewActionClass);
	Actions.Add(NewAction);
}

void URogueActionSystemComponent::StartAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			if (Action->CanStart())
			{	
				Action->StartAction();
			}
			return;
		}
		
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Action %s not found"), *InActionName.ToString());
}

void URogueActionSystemComponent::StopAction(FGameplayTag InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
		
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Action %s not found"), *InActionName.ToString());
}

void URogueActionSystemComponent::ApplayAttributeChange(FGameplayTag AttributeTag, float Delta, EAttributeModifyType ModifyType /*=Base*/)
{
	FRogueAttribute* FoundAttribute = GetAttribute(AttributeTag);
	check(FoundAttribute);
	
	float OldValue = FoundAttribute->GetValue();
	

	switch (ModifyType)
	{
	case Base:
		FoundAttribute->Modifier += Delta;
		break;
		
	case Modifier:
		FoundAttribute->Modifier += Delta;
		break;
		
	case OverrideBase:
		FoundAttribute->Base = Delta;
		break;
	
	default:
		check(false);
	}
	
	RogueAttributeSet->PostAttributeChanged();

	if (FOnAttributeChanged* Event = AttributeListeners.Find(AttributeTag))
	{
		Event->Broadcast(AttributeTag, FoundAttribute->GetValue(),OldValue);
	}
	
	UE_LOGFMT(LogTemp, Log, "Attribute {0} change:  New = {1},  Old = {2}", 
		AttributeTag.ToString(),
		FoundAttribute->GetValue(),
		OldValue
	);
	
}

bool URogueActionSystemComponent::IsAttributeFull(FGameplayTag InAttributeTag, FGameplayTag AttributeMaxTag)
{
	FRogueAttribute* FoundAttribute = GetAttribute(InAttributeTag);
	check(FoundAttribute);
	
	FRogueAttribute* FoundAttributeMax = GetAttribute(AttributeMaxTag);
	check(FoundAttributeMax);
	
	UE_LOGFMT(LogTemp, Log, "Attribute {Att} value: {value}, Attribute {AttMax} value: {valueMax}",
		("Att", InAttributeTag.ToString()),
		("AttMax", AttributeMaxTag.ToString()),
		("value", FoundAttribute->GetValue()),
		("valueMax", FoundAttributeMax->GetValue())
		);

	return FMath::IsNearlyEqual(FoundAttribute->GetValue(), FoundAttributeMax->GetValue());
}

FOnAttributeChanged& URogueActionSystemComponent::GetAttributeListener(FGameplayTag InAttributeTag)
{
	return AttributeListeners.FindOrAdd(InAttributeTag);
}

FRogueAttribute* URogueActionSystemComponent::GetAttribute(FGameplayTag InAttributeTag)
{
	FRogueAttribute** FoundAttribute= CachedAttributes.Find(InAttributeTag);
	return *FoundAttribute;
}



