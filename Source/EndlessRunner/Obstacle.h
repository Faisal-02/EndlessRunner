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

	virtual void BeginPlay() override;



	//-----Variables-----//
	
	//-----Pointers-----//
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent* StaticMesh;
	//-----Functions-----//
	UFUNCTION()
	void OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
