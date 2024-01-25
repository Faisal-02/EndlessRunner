// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class ENDLESSRUNNER_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();



public:	

	//-----Variables-----//
	
	//-----Pointers-----//
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* StaticMesh;
	//-----Functions-----//
	UFUNCTION()
	void OnObstcaleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
