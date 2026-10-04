// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueHealthPickup.h"

#include "RogueGameplayTags.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Core/RogueGameplayStatics.h"


// Sets default values
ARogueHealthPickup::ARogueHealthPickup()
{

}

void ARogueHealthPickup::OnActorOverlapped( UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)|| bIsPickedUp)
	{
		return;
	}
	
	URogueActionSystemComponent* OtherActorActionComp =  OtherActor->GetComponentByClass<URogueActionSystemComponent>();
	//Ensure 
	if (ensure(OtherActorActionComp != nullptr) && !URogueGameplayStatics::IsFullHealth(OtherActorActionComp))
	{
		OtherActorActionComp->ApplayAttributeChange(RogueGameplayTags::Attribute_Health, HealingAmount);
		UGameplayStatics::PlaySound2D(this, PickupSound);
		bIsPickedUp = true;
		Destroy();
	}
}
