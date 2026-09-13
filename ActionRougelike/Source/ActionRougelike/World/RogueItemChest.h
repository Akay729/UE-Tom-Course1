// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionRougelike/Core/RogueInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ARogueItemChest : public AActor, public IRogueInteractionInterface 
{
	GENERATED_BODY()

protected:
		
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "LidAnimation")
	float CurrentAnimationLidPitch = 0.0f;
	
	UPROPERTY(EditAnywhere, Category = "LidAnimation")
	float LidPitch = 120.f;
	
	UPROPERTY(EditAnywhere, Category = "LidAnimation")
	float InterpSpeed = 50.f;

public:
	
	virtual void Interact() override;
	
	virtual void Tick(float DeltaTime) override;
	
	ARogueItemChest();
};
