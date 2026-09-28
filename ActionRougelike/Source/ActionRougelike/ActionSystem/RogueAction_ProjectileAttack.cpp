// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction_ProjectileAttack.h"

#include "NiagaraFunctionLibrary.h"
#include "RogueActionSystemComponent.h"
#include "RogueGameTypes.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Projectile/RogueProjectile.h"


TAutoConsoleVariable<float> CVarProjectileAdjustmentDebugDrawing(TEXT("game.playercharacter.DebugDrawing"), false,
                                                                 TEXT("Enable debug drawing (0=Off, 1=On)"), ECVF_Cheat);


URogueAction_ProjectileAttack::URogueAction_ProjectileAttack()
{
	
}

void URogueAction_ProjectileAttack::StartAction()
{
	Super::StartAction();
	URogueActionSystemComponent* ActionComp = GetOwningComponent();
	ACharacter* Character = CastChecked<ACharacter>(ActionComp->GetOwner());
	
	Character->PlayAnimMontage(AttackMontage);
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, Character->GetMesh(), MuzzleSocketName, FVector::ZeroVector, 
		FRotator::ZeroRotator,EAttachLocation::Type::SnapToTarget,true);
	UGameplayStatics::PlaySound2D(this,ChargeSoundEffect);
	
	FTimerHandle AttackTimerHandle;
	constexpr float AttackDelayTime = 0.2f;
	
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &URogueAction_ProjectileAttack::AttackTimerEnlapsed, AttackDelayTime, false);
	
}

void URogueAction_ProjectileAttack::AttackTimerEnlapsed()
{
	URogueActionSystemComponent* ActionComp = GetOwningComponent();
	ACharacter* Character = CastChecked<ACharacter>(ActionComp->GetOwner());
	
	FVector SpawnLocation = Character->GetMesh()->GetSocketLocation(MuzzleSocketName);
	
	FVector EyeLocation;
	FRotator EyeRotation;
	Character->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);
	
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 5000.f);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Character);
	
	UWorld* World = GetWorld();
	
	FVector AdjustTargetlocation;
	FHitResult HitResult;
	if (World->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, COLLISION_PROJECTILE, QueryParams))
	{
		AdjustTargetlocation = HitResult.Location;
	}
	else
	{
		AdjustTargetlocation = TraceEnd;
	}
	
	FRotator SpawnRotation = (AdjustTargetlocation - SpawnLocation).Rotation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Character;
	//Devo controllare meglio questa riga
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	
	
	AActor* NewActor = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	Character->MoveIgnoreActorAdd(NewActor);
	
	//DEBUG
#if !UE_BUILD_SHIPPING
	float LifetimeDebugDuration = CVarProjectileAdjustmentDebugDrawing.GetValueOnGameThread();
	
	if (LifetimeDebugDuration > 0.f)
	{
		//Adjusted Line Trace
		DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Green, false, LifetimeDebugDuration);
		
		//New projectile Path
		DrawDebugLine(World, SpawnLocation, AdjustTargetlocation, FColor::Green, false, LifetimeDebugDuration);
		//Hit Location or Trace end
		DrawDebugBox(World, AdjustTargetlocation, FVector(20.f),  FColor::Yellow, false,
			LifetimeDebugDuration);
		//Old projectile Path 
		DrawDebugLine(World, SpawnLocation, SpawnLocation + (EyeRotation.Vector()*5000.0f), 
			FColor::Purple, false, LifetimeDebugDuration);
		
	}
#endif
}