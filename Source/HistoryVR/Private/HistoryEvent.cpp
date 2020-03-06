// Fill out your copyright notice in the Description page of Project Settings.


#include "HistoryEvent.h"
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
AHistoryEvent::AHistoryEvent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NodeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeScene"));
	NodeSceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RootComponent = NodeSceneComponent;
	
	P_OrangeEllipse = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	P_OrangeEllipse->SetupAttachment(RootComponent);
	P_OrangeEllipse->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>orange(TEXT("ParticleSystem'/Game/Particles/P_OrangeEllipse.P_OrangeEllipse'"));
	P_OrangeEllipse->SetTemplate(orange.Object);
	
	P_Sparkles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem2"));
	P_Sparkles->SetupAttachment(RootComponent);
	P_Sparkles->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>sparkles(TEXT("ParticleSystem'/Game/Particles/P_Sparkles.P_Sparkles'"));
	P_Sparkles->SetTemplate(sparkles.Object);

	ConstructorHelpers::FObjectFinder<UPaperSprite> h_govermntSprite(TEXT("PaperSprite'/Game/Sprites/govermnt_Sprite.govermnt_Sprite'"));
	ConstructorHelpers::FObjectFinder<UPaperSprite> h_peopleSprite(TEXT("PaperSprite'/Game/Sprites/people_Sprite.people_Sprite'"));
	ConstructorHelpers::FObjectFinder<UPaperSprite> h_placeSprite(TEXT("PaperSprite'/Game/Sprites/place_Sprite.place_Sprite'"));
	ConstructorHelpers::FObjectFinder<UPaperSprite> h_eventSprite(TEXT("PaperSprite'/Game/Sprites/event_Sprite.event_Sprite'"));
	govermntSprite = h_govermntSprite.Object;
	peopleSprite = h_peopleSprite.Object;
	placeSprite = h_placeSprite.Object;
	eventSprite = h_eventSprite.Object;
	
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
void AHistoryEvent::BeginPlay()
{
	Super::BeginPlay();
	P_OrangeEllipse->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));//FMath::VRand()
}

void AHistoryEvent::Create(int32 id, int32 total, bool random)
{
	//bool random = random;
	Id = id;
	float radius = 150.f;
	FVector location = GetActorLocation();
	if (total > 60) radius = total * 3.5f;
	if (random) {
		location += FVector(FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius), FMath::FRandRange(-radius, radius));
	}
	else {
		radius += 200.f;
		int32 countInRow = pow(total, 1.0 / 3);
		int32 step = radius / countInRow;
		int32 x, y, z;
		x = (id-1) % countInRow;
		y = (id - 1) / pow(countInRow, 2); 
		z = (id - 1 - y * pow(countInRow, 2)) / countInRow;
		location += FVector( x * step, y * step, z * step);
		//UKismetSystemLibrary::PrintString(this, FString::FromInt(id) + " " + FString::FromInt(x) + " " + FString::FromInt(y)+ " " + FString::FromInt(z), true, true, FLinearColor(5, 5, 5, 1), 100.f);
	}

	//float roll;
	/*if (Id == 1) roll = 90.f;
	if (Id > 1 && Id < 6) roll = 30.f;
	if (Id > 5 && Id < 10) roll = -30.f;
	if (Id == 10) roll = -90.f;
	FRotator rotation = FRotator(roll, Id * 90.f + 20.f, roll);
	SetActorRotation(rotation);*/
	//FVector location = GetActorForwardVector() * radius;
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
	if (Type == "people") SpriteComponent->SetSprite(peopleSprite);
	if (Type == "govermnt") SpriteComponent->SetSprite(govermntSprite);
	if (Type == "event") SpriteComponent->SetSprite(eventSprite);
	if (Type == "place") SpriteComponent->SetSprite(placeSprite);
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
	//if (SpriteComponent->OnClicked()) SetActorScale3D(FVector(2.f, 2.f, 2.f));
	if (IsCurrent) { SetActorScale3D(FVector(2.f, 2.f, 2.f)); P_Sparkles->SetVisibility(true);  }
	else { SetActorScale3D(FVector(1.f, 1.f, 1.f)); P_Sparkles->SetVisibility(false);
	}
}

