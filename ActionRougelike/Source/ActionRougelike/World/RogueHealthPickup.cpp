// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueHealthPickup.h"

#include "ActionSystem/RogueActionSystemComponent.h"
#include "Kismet/GameplayStatics.h"


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
	if (ensure(OtherActorActionComp != nullptr) && !OtherActorActionComp->IsFullHealth())
	{
		OtherActorActionComp->ApplayHealthChange(HealingAmount);
		UGameplayStatics::PlaySound2D(this, PickupSound);
		bIsPickedUp = true;
		Destroy();
	}
}
