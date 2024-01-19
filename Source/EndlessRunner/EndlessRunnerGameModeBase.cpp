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
	for (int i = 0; i <=NumInitialFloorTiles; i++)
	{
		AddFloorTile();
	}
}

void AEndlessRunnerGameModeBase::AddFloorTile()
{
	UWorld* World = GetWorld();

	if (World)
	{
		AFloorTile* Tile = World -> SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);


		if (Tile)
		{
        	NextSpawnPoint = Tile -> GetAttachTransform();
		}
	}

	
}
