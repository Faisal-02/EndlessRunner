// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerGameModeBase.h"

#include "FloorTile.h"

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	CreateInitialFloorTile();
}

void AEndlessRunnerGameModeBase::CreateInitialFloorTile()
{
	
	AFloorTile* Tile = AddFloorTile();

	if (Tile)
	{
		LanesSwitchValue.Add(Tile -> LeftLane -> GetComponentLocation().Y);
		LanesSwitchValue.Add(Tile -> CenterLane -> GetComponentLocation().Y);
		LanesSwitchValue.Add(Tile -> RightLane -> GetComponentLocation().Y);
	}
	
	for(float Val : LanesSwitchValue)
	{
		UE_LOG(LogTemp, Warning, TEXT("Val = %f"), Val);
	}
	
	
	for (int i = 0; i <NumInitialFloorTiles; i++)
	{
		AddFloorTile();
		
	}
}

AFloorTile* AEndlessRunnerGameModeBase::AddFloorTile()
{
	UWorld* World = GetWorld();

	if (World)
	{
		AFloorTile* Tile = World -> SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);


		if (Tile)
		{
        	NextSpawnPoint = Tile -> GetAttachTransform();
		}

		return Tile; 
	}

	return nullptr;
}
