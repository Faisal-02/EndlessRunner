// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "RunCharacter.h"

// Sets default values
AObstacle::AObstacle()
{
 	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	StaticMesh -> SetupAttachment(SceneComponent);

	
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh -> OnComponentHit.AddDynamic(this, &AObstacle::OnObstacleHit);
}

void AObstacle::OnObstacleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	
	if (ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor))
	{
		RunCharacter -> Death();
	}
	
	
}





