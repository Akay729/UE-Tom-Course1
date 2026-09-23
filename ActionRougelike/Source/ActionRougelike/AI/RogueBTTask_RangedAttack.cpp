// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBTTask_RangedAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Projectile/RogueProjectile.h"

EBTNodeResult::Type URogueBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	AAIController* Controller = OwnerComp.GetAIOwner();
	ACharacter* OwnerCharacter = Cast<ACharacter>(Controller->GetPawn());
	check(OwnerCharacter);
	
	FVector SpawnLocation = OwnerCharacter->GetMesh()->GetSocketLocation(MuzzleSocketName);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	check(BBComp);
	AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
	if (!IsValid(TargetActor))
	{
		return EBTNodeResult::Failed;
	}
	
	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector Direction =  TargetLocation - SpawnLocation;
	FRotator SpawnRotation = Direction.Rotation();
	
	SpawnRotation.Pitch += FMath::FRandRange(-0, MaxBulletSpread);
	SpawnRotation.Yaw += FMath::FRandRange(-MaxBulletSpread, MaxBulletSpread);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = OwnerCharacter;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	
	AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	OwnerCharacter->MoveIgnoreActorAdd(NewProj);
	
	return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
