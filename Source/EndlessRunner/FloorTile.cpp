// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"

#include "EndlessRunnerGameModeBase.h"
#include "Obstacle.h"
#include "RunCharacter.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor Mesh"));
	FloorMesh -> SetupAttachment(SceneComponent);

	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Attach Point"));
	AttachPoint -> SetupAttachment(SceneComponent);
	
	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Center Lane"));
	CenterLane -> SetupAttachment(SceneComponent);
	
	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Left Lane"));
	LeftLane -> SetupAttachment(SceneComponent);
	
	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("Right Lane"));
	RightLane -> SetupAttachment(SceneComponent);

	FloorTrigger =  CreateDefaultSubobject<UBoxComponent>(TEXT("Floor Trigger"));
	FloorTrigger -> SetupAttachment(SceneComponent);
	FloorTrigger -> SetBoxExtent(FVector(32.f,500.f,200.f));
	//Remember to try the different Collision Profiles Names to see the output for each 1 and learn 
	FloorTrigger -> SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();

	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	check(RunGameMode);
	
	FloorTrigger -> OnComponentBeginOverlap.AddDynamic(this, &AFloorTile::OnTriggerBoxOverlap);
	
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}



void AFloorTile::SpawnItem()
{
	if (IsValid(SmallObstacleClass) && IsValid(BigObstacleClass))
	{
		LaneSpawnItem(CenterLane);
		LaneSpawnItem(LeftLane);
		LaneSpawnItem(RightLane);
	}
	
}

void AFloorTile::LaneSpawnItem(UArrowComponent* Lane)
{

	const float RandVal = FMath::FRandRange(0.f, 1.f);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FTransform& SpawnLocation = Lane-> GetComponentTransform();
	
	if (UKismetMathLibrary::InRange_FloatFloat(RandVal, 0.5f, 0.75f, true, true))
	{
		
		AObstacle* Obstacle	= GetWorld() -> SpawnActor<AObstacle>(SmallObstacleClass, SpawnLocation);
	}
	
	else if (UKismetMathLibrary::InRange_FloatFloat(RandVal, 0.75f, 1.f, true, true))
	{
		
		AObstacle* Obstacle	= GetWorld() -> SpawnActor<AObstacle>(BigObstacleClass, SpawnLocation);
	}

	
}

void AFloorTile::OnTriggerBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor);

	if (RunCharacter)
	{
		RunGameMode -> AddFloorTile(true);

		GetWorld() -> GetTimerManager().SetTimer(TimerHandle, this, &AFloorTile::DestroyFloorTile, 2.f, false);
	}
}

void AFloorTile::DestroyFloorTile()
{
	if (TimerHandle.IsValid())
	{
		GetWorld() -> GetTimerManager().ClearTimer(TimerHandle);

		this -> Destroy();
		
	}
}