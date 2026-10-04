// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RoguePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameplayTagContainer.h"
#include "RogueGameplayTags.h"


// Sets default values
ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComponent"));
	
}

// Called to bind functionality to input
void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Ho dovuto includere in questa maniere, il MappingContext perchè dal project setting non andava
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Movement
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::MoveAction);
	EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::LookAction);
	
	EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Started, this, &ThisClass::StartAction, RogueGameplayTags::Action_Sprint.GetTag());
	EnhancedInputComponent->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ThisClass::StopAction, RogueGameplayTags::Action_Sprint.GetTag());
	//Attacks
	EnhancedInputComponent->BindAction(IA_AbilityTeleport, ETriggerEvent::Triggered, this, &ThisClass::StartAction, RogueGameplayTags::Action_SecondaryAttack.GetTag());
	EnhancedInputComponent->BindAction(IA_PrimaryAttack, ETriggerEvent::Triggered, this, &ThisClass::StartAction, RogueGameplayTags::Action_PrimaryAttack.GetTag());
	EnhancedInputComponent->BindAction(IA_AbilityBlackhole, ETriggerEvent::Triggered, this, &ThisClass::StartAction, RogueGameplayTags::Action_SpecialAttack.GetTag());
	
	//Jump
	EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Jump);
}

void ARoguePlayerCharacter::MoveAction(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2D>();
	
	/*Con questo metodo i comandi sono in base la prospettiva di chi conrolla il pawn e non
	 *in base al pawn stesso, la soluzione commentata usa GetActorForwardVector() per riferirsi al pawn    
	 */
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	
	// Forward-Back
	AddMovementInput(ControlRot.Vector(), MoveVector.X);
	
	// Left-Right
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, MoveVector.Y);
	
	//AddMovementInput(GetActorForwardVector(), MoveVector.X);
	//AddMovementInput(GetActorRightVector(), MoveVector.Y);
}

void ARoguePlayerCharacter::LookAction(const FInputActionInstance& value)
{
	FVector2D LookVector = value.GetValue().Get<FVector2D>();
	
	//Serve mettere *-1 per avere i controller 
	AddControllerPitchInput(LookVector.Y*-1);
	AddControllerYawInput(LookVector.X);
}

void ARoguePlayerCharacter::StartAction(FGameplayTag InActionName)
{
	ActionSystemComponent->StartAction(InActionName);
}

void ARoguePlayerCharacter::StopAction(FGameplayTag InActionName)
{
	ActionSystemComponent->StopAction(InActionName);
}

void ARoguePlayerCharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	if(FMath::IsNearlyZero(NewHealth) || NewHealth <= 0.0f)
	{
		DisableInput(nullptr);
		GetMovementComponent()->StopMovementImmediately();
		PlayAnimMontage(DeathMontage);
	}
}

float ARoguePlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                        class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	ActionSystemComponent->ApplayAttributeChange(RogueGameplayTags::Attribute_Health, -ActualDamage, Base);
	
	return ActualDamage;
}

void ARoguePlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &ARoguePlayerCharacter::OnHealthChanged);
}
