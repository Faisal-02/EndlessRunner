// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ArrowComponent.h"
#include "FloorTile.generated.h"


class AObstacle;
class UBoxComponent;
class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class ENDLESSRUNNER_API AFloorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//-----Variables-----//

	UPROPERTY(VisibleAnywhere, Category = "Timer")
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AObstacle> SmallObstacleClass;
	
	//-----Pointers-----//
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* FloorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* AttachPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* CenterLane;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* LeftLane;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UArrowComponent* RightLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* FloorTrigger;

	UPROPERTY(VisibleAnywhere)
	class AEndlessRunnerGameModeBase* RunGameMode;
	
	
	//-----Functions-----//

	
	FORCEINLINE const FTransform& GetAttachTransform() const
	{
		return AttachPoint -> GetComponentTransform();
	}

	UFUNCTION()
	void OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void DestroyFloorTile();

	UFUNCTION(BlueprintCallable)
	void SpawnItem();

	UFUNCTION(BlueprintCallable)
	void LaneSpawnItem(UArrowComponent* Lane);
	

	



};
