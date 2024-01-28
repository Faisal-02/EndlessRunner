// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinItem.h"

#include "EndlessRunnerGameModeBase.h"
#include "RunCharacter.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACoinItem::ACoinItem()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	RootComponent = SceneComponent;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Component"));
	CollisionSphere -> SetupAttachment(SceneComponent);
	CollisionSphere -> SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	CoinMesh -> SetupAttachment(CollisionSphere);
	
	RotatingComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Component"));
	RotatingComponent -> RotationRate = FRotator(0, 180, 0);
}

// Called when the game starts or when spawned
void ACoinItem::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere -> OnComponentBeginOverlap.AddDynamic(this, &ACoinItem::OnCoinOverlap);
}

void ACoinItem::OnCoinOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARunCharacter* RunCharacter = Cast<ARunCharacter>(OtherActor);
	
	if ( RunCharacter && PickupSound)
	{
		RunCharacter -> AddCoin();
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		this -> Destroy();
	}

}









