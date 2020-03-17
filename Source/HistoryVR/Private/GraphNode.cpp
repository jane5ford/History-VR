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
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"


// Sets default values
AGraphNode::AGraphNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NodeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeScene"));
	NodeSceneComponent->bEditableWhenInherited = true;
	RootComponent = NodeSceneComponent;
	static ConstructorHelpers::FObjectFinder<UParticleSystem>orange(TEXT("ParticleSystem'/Game/Particles/P_OrangeEllipse.P_OrangeEllipse'"));
	P_OrangeEllipse = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	P_OrangeEllipse->SetupAttachment(RootComponent);
	P_OrangeEllipse->bEditableWhenInherited = true;
	P_OrangeEllipse->SetTemplate(orange.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>sparkles(TEXT("ParticleSystem'/Game/Particles/P_Sparkles.P_Sparkles'"));
	P_Sparkles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem2"));
	P_Sparkles->bEditableWhenInherited = true;
	P_Sparkles->SetupAttachment(RootComponent);
	P_Sparkles->SetTemplate(sparkles.Object);
	P_Sparkles->SetVisibility(false);
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
	TextDescription = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Description"));
	TextDescription->SetupAttachment(RootComponent);
	TextDescription->bEditableWhenInherited = true;
	TextDescription->SetHorizontalAlignment(EHTA_Center);
	TextDescription->SetWorldSize(8.f);
	TextDescription->SetTextRenderColor(FColor(255, 174, 0, 255));
	TextDate = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Date"));
	TextDate->SetupAttachment(RootComponent);
	TextDate->bEditableWhenInherited = true;
	TextDate->SetHorizontalAlignment(EHTA_Center);
	TextDate->SetWorldSize(6.f);
	this->AutoReceiveInput = EAutoReceiveInput::Player0;
	//SpriteComponent->OnClicked.AddDynamic(this, &AGraphNode::PickNode);
	//InputComponent->BindAction("PickNode", IE_Pressed, this, &AGraphNode::PickNodes);
}

// Called when the game starts or when spawned
void AGraphNode::BeginPlay()
{
	Super::BeginPlay();
	P_OrangeEllipse->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));//FMath::VRand()
	
}

FVector AGraphNode::GenerateLocation()
{
	float radius = 300;
	FVector location = FVector(FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius));
	NodeSceneComponent->MoveComponent(location, FRotator(0, 0, 0), false);
	return location;
}

void AGraphNode::Locate(int32 nodeId, int32 total, bool random)
{
	Id = nodeId;
	Total = total;
	int step = 120;
	FVector location = GetActorLocation();
	if (random) {
		float radius = step / 1.5 * pow(total, 1.0 / 3);
		location += FVector(FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius));
	}
	else {
		int32 countInRow = pow(total, 1.0 / 3);
		int32 x, y, z;
		x = (Id - 1) % countInRow;
		y = (Id - 1) / pow(countInRow, 2);
		z = (Id - 1 - y * pow(countInRow, 2)) / countInRow;
		location += FVector( x * step, y * step, z * step) - (countInRow * step) / 2;
	}
	SetActorLocation(location);	
}

void AGraphNode::SetData(FString description, FString date, FString type) {
	Description = description;
	TextDescription->SetText(Description);
	Date = date;
	TextDate->SetText(Date);
	Type = type;
}

void AGraphNode::RotateToPlayer()
{
	if (Rotable) {
		FVector playerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerLoc));
	}	
}

// Called every frame
void AGraphNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateToPlayer();
}



void AGraphNode::PickNode(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	UKismetSystemLibrary::PrintString(this, "Pressed", true, true, FLinearColor(5, 5, 5, 1), 100.f);
	P_OrangeEllipse->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
}

void AGraphNode::PickNodes()
{
	UKismetSystemLibrary::PrintString(this, "Pressed V", true, true, FLinearColor(5, 5, 5, 1), 100.f);
	P_OrangeEllipse->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
}


