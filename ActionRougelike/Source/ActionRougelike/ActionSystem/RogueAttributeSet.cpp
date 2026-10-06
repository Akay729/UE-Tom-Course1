// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAttributeSet.h"

#include "RogueActionSystemComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


//HEALTH ATTRIBUTE
URogueHealthAttributeSet::URogueHealthAttributeSet()
{
	Health =  FRogueAttribute(100);
	HealthMax = FRogueAttribute(Health.GetValue());
}


void URogueHealthAttributeSet::PostAttributeChanged()
{
	Health.Base = FMath::Clamp(Health.Base, 0.f, HealthMax.GetValue());
}


//PAWN ATTRIBUTE
URoguePawnAttributeSet::URoguePawnAttributeSet()
{
	MovementSpeed = FRogueAttribute(550);
}

void URoguePawnAttributeSet::InitializeAttributes()
{
	Super::InitializeAttributes();
	ApplyMoveSpeed();
}

void URoguePawnAttributeSet::PostAttributeChanged()
{
	Super::PostAttributeChanged();
	ApplyMoveSpeed();

}

void URoguePawnAttributeSet::ApplyMoveSpeed()
{
	ACharacter* Character = Cast<ACharacter>(GetOwningComponent()->GetOwner());
	Character->GetCharacterMovement()->MaxWalkSpeed = MovementSpeed.GetValue();
}




//MONSTER ATTRIBUTE
URogueMonsterAttributeSet::URogueMonsterAttributeSet()
{
	MovementSpeed = FRogueAttribute(450);
}


URogueActionSystemComponent* URogueAttributeSet::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}
