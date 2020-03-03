// Fill out your copyright notice in the Description page of Project Settings.


#include "HistoryEdge.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AHistoryEdge::AHistoryEdge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//NodeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NodeMesh"));
	NodeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeScene"));
	NodeSceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RootComponent = NodeSceneComponent;
	//NodeMeshComponent->SetupAttachment(RootComponent);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/Game/Geometry/Meshes/Shape_Cylinder.Shape_Cylinder'"));
	//NodeMeshComponent->SetStaticMesh(MeshAsset.Object);
	//NodeMeshComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	PS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem'/Game/Particles/P_Beam_Laser_Ice.P_Beam_Laser_Ice'"));
	PS->SetupAttachment(RootComponent);
	PS->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PSRay(TEXT("ParticleSystem'/Game/Particles/P_Beam_Laser_Ice.P_Beam_Laser_Ice'"));
	
	PS->SetTemplate(PSRay.Object);
}

// Called when the game starts or when spawned
void AHistoryEdge::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHistoryEdge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Rotate and Scale Edge depends of NodeA
	float edge_distance = FVector::Dist(NodeA->GetActorLocation(), NodeB->GetActorLocation());
	PS->SetFloatParameter("Lenght", edge_distance);
	//NodeMeshComponent->SetWorldScale3D(FVector(0.02f, 0.02f, edge_distance * 0.01f));
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(NodeB->GetActorLocation(), NodeA->GetActorLocation());
	this->SetActorLocationAndRotation(NodeB->GetActorLocation(), rotation);
}

void AHistoryEdge::Create(AHistoryEvent* nodeA, AHistoryEvent* nodeB) 
{
	NodeA = nodeA; NodeB = nodeB;
}

