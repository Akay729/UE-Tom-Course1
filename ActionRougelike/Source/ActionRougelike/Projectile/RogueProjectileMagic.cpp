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
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	
	FVector DirectionHit =  GetActorRotation().Vector();
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, DirectionHit, Hit, GetInstigatorController(),
		this, DmgTypeClass);
	
	//UGameplayStatics::ApplyDamage(OtherActor, 10.f, GetInstigatorController(), this, DmgTypeClass);
	
	/* Qua si poteva usare FHitResult.HitLocation per una cordinata migliore al posto di GetActorLocation()
	 * Dato che il primo da la cordinata della collisione ed il secondo quella del attore in question (il proittile) 
	*/
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	
	UGameplayStatics::PlaySoundAtLocation(this, HitSoundEffect, GetActorLocation(),FRotator::ZeroRotator);
	Destroy();
}

