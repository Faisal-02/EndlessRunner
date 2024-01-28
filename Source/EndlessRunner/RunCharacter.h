// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunCharacter.generated.h"

UCLASS()
class ENDLESSRUNNER_API ARunCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
	//-----Variables-----//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentLane = 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 NextLane = 0;

	FTimerHandle RestartLevelHandle;
	
	//-----Pointers-----//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	
	class UCharacterMovementComponent* MovementComponent;

	class AEndlessRunnerGameModeBase* RunGameMode;

	UPROPERTY(EditAnywhere, Category = "Assets")
	class UParticleSystem* DeathParticleSystem;

	UPROPERTY(EditAnywhere, Category = "Assets")
	USoundBase* DeathSound;

	UPROPERTY(VisibleAnywhere)
	bool bIsDead = false;

	
	
	//-----Functions-----//
	
	UFUNCTION()
	void MoveLeft();

	UFUNCTION()
	void MoveRight();

	UFUNCTION()
	void MoveDawn();

	void Running();

	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
	void ChangeLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneUpdate(float Alpha);

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneFinished();

	UFUNCTION(BlueprintCallable, Category = "EndGame")
	void Death();
	
	UFUNCTION(BlueprintCallable, Category = "EndGame")
	void AfterDeath();

	UFUNCTION(BlueprintCallable, Category = "EndGame")
	void AddCoin();
};
