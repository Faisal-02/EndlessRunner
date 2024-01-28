// Fill out your copyright notice in the Description page of Project Settings.
#include "RunCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EndlessRunnerGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARunCharacter::ARunCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	
	SpringArm -> TargetArmLength = 350.f;
	SpringArm -> SocketOffset = FVector(0.f,0.f,100.f);
	SpringArm -> bUsePawnControlRotation = true;
	SpringArm -> SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//false cuz its used by SpringArm
	CameraComponent -> bUsePawnControlRotation = false;
	CameraComponent -> SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	
	//Change properties of MovementComponent
    if (MovementComponent)
    {
    	MovementComponent -> MaxWalkSpeed = 1500.f;
    	MovementComponent -> JumpZVelocity = 600.f;
    	MovementComponent -> AirControl = 0.2f;
    }
}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(this));	
}

// Called every frame
void ARunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Running();
}

// Called to bind functionality to input
void ARunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAction("MoveLeft", IE_Pressed, this, &ARunCharacter::MoveLeft);
	PlayerInputComponent -> BindAction("MoveRight", IE_Pressed, this, &ARunCharacter::MoveRight);
	PlayerInputComponent -> BindAction("MoveDown", IE_Pressed, this, &ARunCharacter::MoveDawn);

	PlayerInputComponent -> BindAction("Jump", IE_Pressed, this, &ARunCharacter::Jump);
	PlayerInputComponent -> BindAction("Jump", IE_Released, this, &ARunCharacter::StopJumping);
}

void ARunCharacter::MoveLeft()
{

	NextLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	ChangeLane();
	
	
}

void ARunCharacter::MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane + 1, 0, 2);
	ChangeLane();
	
	
}

void ARunCharacter::MoveDawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Dawn"));
}



void ARunCharacter::Running()
{
	AddMovementInput(GetActorForwardVector(), 1);
}

void ARunCharacter::ChangeLaneUpdate(float Alpah)
{
	FVector CharLocation = GetCapsuleComponent() -> GetComponentLocation();
	CharLocation.Y = FMath::Lerp(RunGameMode -> LanesSwitchValue[CurrentLane], RunGameMode -> LanesSwitchValue[NextLane], Alpah);
	SetActorLocation(CharLocation);
	
}

void ARunCharacter::ChangeLaneFinished()
{
	CurrentLane = NextLane;
}

void ARunCharacter::Death()
{
	if (!bIsDead)
	{
		const FVector Location = GetActorLocation();
		const UWorld* World = GetWorld();
        	if (World)
        	{
        		bIsDead = true;
        		
        		if (DeathParticleSystem)
        		{
        			UGameplayStatics::SpawnEmitterAtLocation(World, DeathParticleSystem, Location);
        		}
        		
        		if (DeathSound)
        		{
        			UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
        		}

        		GetMesh() -> SetVisibility(false);
        		DisableInput(nullptr);
        		
        	}
		World ->GetTimerManager().SetTimer(RestartLevelHandle, this, &ARunCharacter::AfterDeath, 2.f);
	}
		

		
			
	
	
	
}

void ARunCharacter::AfterDeath()
{
	if (RestartLevelHandle.IsValid())
	{
		GetWorld() -> GetTimerManager().ClearTimer(RestartLevelHandle);
	}
	UKismetSystemLibrary::ExecuteConsoleCommand(this, TEXT("RestartLevel"));
	bIsDead = false;
	
}

void ARunCharacter::AddCoin()
{
	if (IsValid(RunGameMode))
	{
		RunGameMode -> AddCoin();
	}
	
}
