// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
ARougeCharacter::ARougeCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 300.0f;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ARougeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARougeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARougeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Ho dovuto includere in questa maniere il MappingContext perchè dal project setting non andava
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ARougeCharacter::MoveAction);
	EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ARougeCharacter::LookAction);
}

void ARougeCharacter::MoveAction(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MoveVector.Y);
	AddMovementInput(GetActorRightVector(), MoveVector.X);
}

void ARougeCharacter::LookAction(const FInputActionValue& value)
{
	
}
