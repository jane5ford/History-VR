// Fill out your copyright notice in the Description page of Project Settings.


#include "Edge.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEdge::AEdge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NodeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeScene"));
	NodeSceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RootComponent = NodeSceneComponent;
	PS = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem'/Game/Particles/P_Beam_Laser_Ice.P_Beam_Laser_Ice'"));
	PS->SetupAttachment(RootComponent);
	PS->SetRelativeLocation(FVector(20.f, 0.f, 0.f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>PSRay(TEXT("ParticleSystem'/Game/Particles/P_Beam_Laser_Ice.P_Beam_Laser_Ice'"));
	PS->SetTemplate(PSRay.Object);
}

// Called when the game starts or when spawned
void AEdge::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEdge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float edge_distance = FVector::Dist(NodeA->GetActorLocation(), NodeB->GetActorLocation()) - 40.f;
	PS->SetFloatParameter("Lenght", edge_distance);
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(NodeB->GetActorLocation(), NodeA->GetActorLocation());
	this->SetActorLocationAndRotation(NodeB->GetActorLocation()+FVector(0.f,0.f,0.f), rotation);
}

void AEdge::Create(AHistoryEvent* nodeA, AHistoryEvent* nodeB) 
{
	NodeA = nodeA; NodeB = nodeB;
}

