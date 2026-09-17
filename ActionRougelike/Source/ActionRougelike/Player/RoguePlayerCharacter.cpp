// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RoguePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile/RogueProjectileMagic.h"
#include "Projectile/RogueProjectileTeleport.h"
#include "Projectile/RogueProjectileBlackhole.h"


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

	MuzzleSocketName = "Muzzle_01";
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
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::MoveAction);
	EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::LookAction);
	EnhancedInputComponent->BindAction(IA_PrimaryAttack, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::PrimaryShoot);
	EnhancedInputComponent->BindAction(IA_AbilityTeleport, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::AbilityTeleport);
	EnhancedInputComponent->BindAction(IA_AbilityBlackhole, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::AbilityBlackhole);
	EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Jump);
}
// Called when the game starts or when spawned
void ARoguePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARoguePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void ARoguePlayerCharacter::PrimaryShoot()
{
	PlayAnimMontage(AttackMontage);
	
	FTimerHandle TimerHandle;
	constexpr float AttackDelayTime = 0.2f;
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName, FVector::ZeroVector, 
		FRotator::ZeroRotator,EAttachLocation::Type::SnapToTarget,true);
	
	UGameplayStatics::PlaySound2D(this,ChargeSoundEffect);
	
	GetWorldTimerManager().SetTimer(TimerHandle, this ,&ARoguePlayerCharacter::AttackTimerEnlapsed, AttackDelayTime);
}


void ARoguePlayerCharacter::AbilityTeleport()
{
	
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	//Devo controllare meglio questa riga
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(TeleportProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	MoveIgnoreActorAdd(NewActor);
	/*PlayAnimMontage(AttackMontage);
	
	FTimerHandle TimerHandle;
	constexpr float AttackDelayTime = 0.2f;
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName, FVector::ZeroVector, 
		FRotator::ZeroRotator,EAttachLocation::Type::SnapToTarget,true);
	UGameplayStatics::PlaySound2D(this,ChargeSoundEffect);
	
	GetWorldTimerManager().SetTimer(TimerHandle, this ,&ARoguePlayerCharacter::AttackTimerEnlapsed, AttackDelayTime);*/
}

void ARoguePlayerCharacter::AbilityBlackhole()
{
	
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	//Devo controllare meglio questa riga
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(BlackholeProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	MoveIgnoreActorAdd(NewActor);

}



void ARoguePlayerCharacter::AttackTimerEnlapsed()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	//Devo controllare meglio questa riga
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(MagicProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	MoveIgnoreActorAdd(NewActor);
}
