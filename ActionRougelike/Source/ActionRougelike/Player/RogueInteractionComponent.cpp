// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"
#include "Engine/OverlapResult.h"

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	FVector Center = PC->GetPawn()->GetActorLocation();
	// DrawDebugBox(GetWorld(), Center, FVector(20.0f), FColor::Green);
	
	TArray<FOverlapResult> OverlapResults;
	// raggio di azione del component interacion
	ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractionRadius);
	
	GetWorld()->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, CollisionChannel, CollisionShape);
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::Silver);
	
	float HighestDotResult;
	AActor* BestActor = nullptr;
	//Note usa "&" per fare riferimento alla variabile e non copiarla!
	for (FOverlapResult& OverlapResult : OverlapResults)
	{
		FVector CurrentActorLocation = OverlapResult.GetActor()->GetActorLocation();
		
		DrawDebugBox(GetWorld(), CurrentActorLocation, FVector(45.0f), FColor::Red);
		
		FVector OverlapDirection = (CurrentActorLocation - Center).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		FString DotString = FString::Printf(TEXT("Dot: %f"), DotResult);
		
		DrawDebugString(GetWorld(), CurrentActorLocation, DotString,0,FColor::White,0.0f);
		
		if (DotResult > HighestDotResult)
		{
			HighestDotResult = DotResult;
			BestActor = OverlapResult.GetActor();
			
		}
		
	}
	if (BestActor)
	{
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.0f), FColor::Green);
	}
	
}

