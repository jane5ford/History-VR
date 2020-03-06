// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNode.h"
#include "HistoryEdge.h"
#include "Graph.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include <Runtime\Engine\Classes\Kismet\KismetSystemLibrary.h>
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AGraphNode::AGraphNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NodeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeScene"));
	NodeSceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RootComponent = NodeSceneComponent;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>orange(TEXT("ParticleSystem'/Game/Particles/P_OrangeEllipse.P_OrangeEllipse'"));
	P_OrangeEllipse = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	P_OrangeEllipse->SetupAttachment(RootComponent);
	P_OrangeEllipse->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	P_OrangeEllipse->SetTemplate(orange.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>sparkles(TEXT("ParticleSystem'/Game/Particles/P_Sparkles.P_Sparkles'"));
	P_Sparkles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem2"));
	P_Sparkles->SetupAttachment(RootComponent);
	P_Sparkles->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	P_Sparkles->SetTemplate(sparkles.Object);
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetRelativeLocation(FVector(0.f, 0.0f, 5.0f));
	SpriteComponent->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
	SpriteComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TextDescription = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Description"));
	TextDescription->SetupAttachment(RootComponent);
	TextDescription->SetHorizontalAlignment(EHTA_Center);
	TextDescription->SetRelativeLocation(FVector(5.0f, 0.0f, -15.0f));
	TextDescription->SetWorldSize(8.f);
	TextDescription->SetTextRenderColor(FColor(255, 174, 0, 255));
	TextDate = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Date"));
	TextDate->SetupAttachment(RootComponent);
	TextDate->SetHorizontalAlignment(EHTA_Center);
	TextDate->SetRelativeLocation(FVector(5.0f, 0.0f, -20.0f));
	TextDate->SetWorldSize(6.f);
}

// Called when the game starts or when spawned
void AGraphNode::BeginPlay()
{
	Super::BeginPlay();
	P_OrangeEllipse->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));//FMath::VRand()
}

void AGraphNode::Locate(int32 id, int32 total, bool random)
{
	Id = id;
	int step = 120;
	FVector location = GetActorLocation();
	if (random) {
		float radius = step / 1.5 * pow(total, 1.0 / 3);
		location += FVector(FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius));
	}
	else {
		int32 countInRow = pow(total, 1.0 / 3);
		int32 x, y, z;
		x = (id - 1) % countInRow;
		y = (id - 1) / pow(countInRow, 2); 
		z = (id - 1 - y * pow(countInRow, 2)) / countInRow;
		location += FVector( x * step, y * step, z * step);
	}
	SetActorLocation(location);	
}

void AGraphNode::SetData(FString description, FString date) {
	Description = description;
	TextDescription->SetText(Description);
	Date = date;
	TextDate->SetText(Date);
}

// Called every frame
void AGraphNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float speed = 0.05f;
	FVector playerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerLoc));
	if (IsCurrent) { SetActorScale3D(FVector(2.f, 2.f, 2.f)); P_Sparkles->SetVisibility(true);  }
	else { SetActorScale3D(FVector(1.f, 1.f, 1.f)); P_Sparkles->SetVisibility(false);}
}

