// Fill out your copyright notice in the Description page of Project Settings.


#include "RunAnimInstance.h"

#include "GameFramework/PawnMovementComponent.h"

void URunAnimInstance::NativeInitializeAnimation()
{
	if (Pawn  == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		MovementComponent = Pawn -> GetMovementComponent();
	}
	
}

void URunAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (Pawn && MovementComponent)
	{
		//IsFalling() is mean player is not on the ground
		bIsInAir = MovementComponent->IsFalling();

		Speed = Pawn->GetVelocity().Size();
	}
}
