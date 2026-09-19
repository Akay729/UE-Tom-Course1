// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectileMagic.h"

#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


ARogueProjectileMagic::ARogueProjectileMagic()
{

}

void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit )
{
	
	FVector DirectionHit =  GetActorRotation().Vector();
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, DirectionHit, Hit, GetInstigatorController(),
		this, DmgTypeClass);
	
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
}

