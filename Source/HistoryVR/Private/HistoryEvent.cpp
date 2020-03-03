// Fill out your copyright notice in the Description page of Project Settings.


#include "HistoryEvent.h"
#include "HistoryEdge.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include <Runtime\Engine\Classes\Kismet\KismetSystemLibrary.h>
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
AHistoryEvent::AHistoryEvent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//NodeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
	//NodeMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -10.0f));
	NodeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeScene"));
	NodeSceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RootComponent = NodeSceneComponent;
	//NodeMeshComponent->SetupAttachment(RootComponent);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/Shape_Sphere.Shape_Sphere'"));
	//NodeMeshComponent->SetStaticMesh(MeshAsset.Object);
	PS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem'/Game/Particles/P_Sparcles.P_Sparcles'"));
	PS->SetupAttachment(RootComponent);
	PS->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PSRay(TEXT("ParticleSystem'/Game/Particles/P_Sparcles.P_Sparcles'"));

	PS->SetTemplate(PSRay.Object);

}

// Called when the game starts or when spawned
void AHistoryEvent::BeginPlay()
{
	Super::BeginPlay();
	PS->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));//FMath::VRand()
}

void AHistoryEvent::Create(int32 id) 
{
	float radius = 80.f;
	Id = id;
	FVector location = GetActorLocation() + FVector(FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius));
	SetActorLocation(location);
}

// Called every frame
void AHistoryEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float speed = 0.05f;
	SetActorLocation(GetActorLocation() + 0.02f* GetActorForwardVector());
	SetActorRotation(GetActorRotation() + FRotator(0.f,0.1f, 0.f));
}

