// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "RogueGameTypes.h"
#include "VectorTypes.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"

TAutoConsoleVariable<bool> CVarInteractionDebugDrawing(TEXT("game.interaction.DebugDraw"), false,
 TEXT("Enable debug drawing (0 = Off, 1 = On)"), ECVF_Cheat);


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
	FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	// DrawDebugBox(GetWorld(), Center, FVector(20.0f), FColor::Green);
	
	TArray<FOverlapResult> OverlapResults;
	// raggio di azione del component interacion
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(InteractionRadius);
	
	float InteractionRadiusSqrd = InteractionRadius * InteractionRadius; 
	
	GetWorld()->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, CollisionChannel, CollisionShape);
	
	bool bEnableDebugDraw = CVarInteractionDebugDrawing.GetValueOnGameThread();
	
	float HighestWeight = -2.0f;
	
	AActor* BestActor = nullptr;
	
	//Note usa "&" per fare riferimento alla variabile e non copiarla!
	for (FOverlapResult& OverlapResult : OverlapResults)
	{
		FVector Origin; //Meglio usare oring di get actor location, molto più consistente se sic son molte mash
		FVector BoxExtends;
		OverlapResult.GetActor()->GetActorBounds(true, Origin, BoxExtends);
		/*
		 *NOTA: Meglio non usare ChildActorComponent... Spawna un actor che si attacca al component ma è molto bugga 
		 *Meglio non usarlo
		*/
		
		
		//FVector CurrentActorLocation = OverlapResult.GetActor()->GetActorLocation();
		FVector OverlapDirection = (Origin - CameraLocation).GetSafeNormal();
		
		float DistanceToSqrd = (Origin - Center).SizeSquared();
		//Normalize Invert smaller distance is higher Weight
		float NormalizedDistanceTo = 1.0f - (DistanceToSqrd / InteractionRadiusSqrd);
		
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
		//Normalize 0.0f to 1.0f
		float NormalizeDotResult = DotResult * 0.5f + 0.5f;
		
		float Weight = (NormalizeDotResult * DirectionWeightScale) + (NormalizedDistanceTo * DistanceToWeightScale) ;
		
		if (Weight > HighestWeight)
		{
			HighestWeight = Weight;
			BestActor = OverlapResult.GetActor();
			
		}
		
		if (bEnableDebugDraw)
		{
			DrawDebugBox(GetWorld(), Origin, FVector(45.0f), FColor::Red);
			FString DebugString = FString::Printf(TEXT("Weight %f , Dot: %f , Dist: %f"), Weight, NormalizeDotResult, NormalizedDistanceTo);
			DrawDebugString(GetWorld(), Origin, DebugString,0,FColor::White,0.0f);
		}
		
	}
	
	SelectedActor = BestActor;
	
	if (bEnableDebugDraw)
	{
		if (SelectedActor)
		{
			DrawDebugBox(GetWorld(), SelectedActor->GetActorLocation(), FVector(60.0f), FColor::Green);
		}
		
		DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::Silver);
	}
	
}

void URogueInteractionComponent::Interact()
{
	
	if (SelectedActor)
	{
	IRogueInteractionInterface::Execute_Interact(SelectedActor);
	}
	
}
