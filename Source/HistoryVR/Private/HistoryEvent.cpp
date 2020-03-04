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
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/TextRenderComponent.h"

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

	static ConstructorHelpers::FObjectFinder<UPaperSprite>Sprite(TEXT("PaperSprite'/Game/Sprites/govermnt_Sprite.govermnt_Sprite'"));
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetSprite(Sprite.Object);
	SpriteComponent->SetRelativeLocation(FVector(0.f, 0.0f, 5.0f));
	SpriteComponent->SetWorldScale3D(FVector(0.05f, 0.05f, 0.05f));
	SpriteComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	//SpriteComponent->SetCollisionEnabled(false);

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
void AHistoryEvent::BeginPlay()
{
	Super::BeginPlay();
	PS->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));//FMath::VRand()
}

void AHistoryEvent::Create(int32 id) 
{
	float radius = 80.f;
	Id = id;
	//FVector location = GetActorLocation() + FVector(FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius));
	float roll;
	if (Id == 1) roll = 90.f;
	if (Id > 1 && Id < 6) roll = 30.f;
	if (Id > 5 && Id < 10) roll = -30.f;
	if (Id == 10) roll = -90.f;
	FRotator rotation = FRotator(roll, Id * 90.f, roll);
	SetActorRotation(rotation);
	FVector location = GetActorForwardVector() * 100.f;
	SetActorLocation(location);	
}

void AHistoryEvent::SetDescription(FString description) {
	Description = description;
	TextDescription->SetText(Description);
}

void AHistoryEvent::SetDate(FString date) {
	Date = date;
	TextDate->SetText(Date);
}

void AHistoryEvent::SetType(FString type)
{
	Type = type;
	/*if (type == "people") static ConstructorHelpers::FObjectFinder<UPaperSprite>Sprite(TEXT("PaperSprite'/Game/Sprites/people_Sprite.people_Sprite'"));
	if (type == "govermnt") static ConstructorHelpers::FObjectFinder<UPaperSprite>Sprite(TEXT("PaperSprite'/Game/Sprites/govermnt_Sprite.govermnt_Sprite'"));
	if (type == "place") static ConstructorHelpers::FObjectFinder<UPaperSprite>Sprite(TEXT("PaperSprite'/Game/Sprites/place_Sprite.place_Sprite'"));
	if (type == "event") static ConstructorHelpers::FObjectFinder<UPaperSprite>Sprite(TEXT("PaperSprite'/Game/Sprites/event_Sprite.event_Sprite'"));
	*/	
	//SpriteComponent->SetSprite(Sprite.Object);
}



// Called every frame
void AHistoryEvent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float speed = 0.05f;
	//SetActorLocation(GetActorLocation() + 0.02f* GetActorForwardVector());
	//SetActorRotation(GetActorRotation() + FRotator(0.f,0.1f, 0.f));
	FVector playerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), playerLoc));
	

}

