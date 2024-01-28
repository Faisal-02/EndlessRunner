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
	//the 3 firsts tiles should not be spawn with any items, then its allow to spawn items
	const AFloorTile* Tile = AddFloorTile(false);
	AddFloorTile(false);
	AddFloorTile(false);

	
	if (Tile)
	{
		LanesSwitchValue.Add(Tile -> LeftLane -> GetComponentLocation().Y);
		LanesSwitchValue.Add(Tile -> CenterLane -> GetComponentLocation().Y);
		LanesSwitchValue.Add(Tile -> RightLane -> GetComponentLocation().Y);
	}
	
	
	for (int i = 0; i <NumInitialFloorTiles; i++)
	{
		AddFloorTile(true);
	}
	
}

AFloorTile* AEndlessRunnerGameModeBase::AddFloorTile(bool bSpawnItems)
{
	

	if (UWorld* World = GetWorld())
	{
		AFloorTile* Tile = World -> SpawnActor<AFloorTile>(FloorTileClass, NextSpawnPoint);


		if (Tile)
		{
			if (bSpawnItems)
			{
				Tile -> SpawnItem();
			}
        	NextSpawnPoint = Tile -> GetAttachTransform();
		}

		return Tile; 
	}

	return nullptr;
}

void AEndlessRunnerGameModeBase::AddCoin()
{
	CoinCounter += 1;
	UE_LOG(LogTemp, Warning, TEXT("ur coins = %i"), CoinCounter);
}
