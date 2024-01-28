// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoinItem.generated.h"

UCLASS()
class ENDLESSRUNNER_API ACoinItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoinItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//-----Variables-----//
	
	
	//-----Pointers-----//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Component")
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Component")
	UStaticMeshComponent* CoinMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Component")
	class URotatingMovementComponent* RotatingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Component")
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Assets")
	USoundBase* PickupSound;
	//-----Functions-----//
	UFUNCTION()
	void OnCoinOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
