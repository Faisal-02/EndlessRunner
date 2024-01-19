// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

class AFloorTile;
/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


	//-----Variables-----//

	FTransform NextSpawnPoint;
	
	
	//-----Pointer-----//
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AFloorTile> FloorTileClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 NumInitialFloorTiles = 10;



	//-----Function-----//
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void CreateInitialFloorTile();

	UFUNCTION(BlueprintCallable)
	void AddFloorTile();
};
