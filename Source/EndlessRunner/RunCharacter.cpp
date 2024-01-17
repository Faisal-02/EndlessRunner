// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "RunCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"

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
    else
    {
    	UE_LOG(LogTemp, Warning, TEXT("Null MovementComponent"));
    }
	
}

// Called when the game starts or when spawned
void ARunCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	UE_LOG(LogTemp, Warning, TEXT("Letf"));
}

void ARunCharacter::MoveRight()
{
	UE_LOG(LogTemp, Warning, TEXT("Right"));
}

void ARunCharacter::MoveDawn()
{
	UE_LOG(LogTemp, Warning, TEXT("Dawn"));
}



void ARunCharacter::Running()
{
	AddMovementInput(GetActorForwardVector(), 1);
}