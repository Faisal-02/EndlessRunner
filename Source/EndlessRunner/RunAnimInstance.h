// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RunAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API URunAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//-----Variables-----//
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	bool bIsInAir;

	//-----Pointers-----//
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	APawn* Pawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	UPawnMovementComponent* MovementComponent;

	//-----Functions-----//
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
