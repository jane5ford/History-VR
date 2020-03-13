// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"
#include "GraphNode.h"
#include "GraphNodePerson.h"
#include "GraphNodeState.h"
#include "GraphNodeEvent.h"
#include "GraphNodePlace.h"
#include "HistoryEdge.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Misc/FileHelper.h"
#include <Runtime\Core\Public\Misc\Paths.h>
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AGraph::AGraph()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	NodeSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("NodeScene"));
	NodeSceneComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	RootComponent = NodeSceneComponent;
}


// Called when the game starts or when spawned
void AGraph::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<FString> nodesArray;
	if (FFileHelper::LoadFileToStringArray(nodesArray, *(FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) +"/Test/Data/" + NodesData))) {
		int32 k = 0;
			FString res;
			FString res1, res2;
			AGraphNode* node;
			int32 total = nodesArray.Num() / 2;
			for (int32 i = 1; i <= total; i++) {
				nodesArray[k].Split(":", &res1, &res2);
				//node = SpawnNode(res1);
				node = (AGraphNode*)SpawnNodeBP(res1);
				if (node) {
					node->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
					node->SetData(res2, nodesArray[k + 1], res1);
					node->Locate(i, total, IsRandom);
					Nodes.Add(i, node);
					k = k + 2;
				}
			}
	}
	else UKismetSystemLibrary::PrintString(this, "File Not Found", true, true, FLinearColor(0, 0, 0, 1), 100.f);

	TArray<FString> adjacencyArray;
	if (FFileHelper::LoadFileToStringArray(adjacencyArray, *(FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + "/Test/" + NodesData))) {
		//FString IntAsString = FString::FromInt();
		//UKismetSystemLibrary::PrintString(this, "Nodes and Edges: " + result[0], true, true, FLinearColor(0, 0, 0, 1), 100.f);
		FString res;
		FString res1, res2;
		for (int32 i = 1; i < adjacencyArray.Num(); i++) {
			res = adjacencyArray[i];
			res.Split(" ", &res1, &res2);
			int32 nodeA_id = FCString::Atoi(*res1);
			int32 nodeB_id = FCString::Atoi(*res2);
			SpawnRelation(i, nodeA_id, nodeB_id);
			Nodes[nodeA_id]->EdgesID.Add(i);
			Nodes[nodeB_id]->EdgesID.Add(i);
		}
	}
	else UKismetSystemLibrary::PrintString(this, "File Not Found", true, true, FLinearColor(0, 0, 0, 1), 100.f);
}

void AGraph::SpawnRelation(int32 id, int32 nodeA_id, int32 nodeB_id) {

	AGraphNode* nodeA;
	AGraphNode* nodeB;
	nodeA = (AGraphNode*)Nodes[nodeA_id];
	nodeB = (AGraphNode*)Nodes[nodeB_id];
	AHistoryEdge* edge = GetWorld()->SpawnActor<AHistoryEdge>();
	edge->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	edge->Create(nodeA, nodeB);
	edge->Id = id;
}

AGraphNode* AGraph::SpawnNode(FString type)
{
	if (type == "person") return GetWorld()->SpawnActor<AGraphNodePerson>(FVector(-60.f, 0.f, 120.f), FRotator(0.f, 0.f, 0.f));
	if (type == "state") return GetWorld()->SpawnActor<AGraphNodeState>(FVector(-60.f, 0.f, 120.f), FRotator(0.f, 0.f, 0.f));
	if (type == "event") return GetWorld()->SpawnActor<AGraphNodeEvent>(FVector(-60.f, 0.f, 120.f), FRotator(0.f, 0.f, 0.f));
	if (type == "place") return GetWorld()->SpawnActor<AGraphNodePlace>(FVector(-60.f, 0.f, 120.f), FRotator(0.f, 0.f, 0.f));
	return GetWorld()->SpawnActor<AGraphNode>(FVector(-60.f, 0.f, 120.f), FRotator(0.f, 0.f, 0.f)); 
}

UFUNCTION()AActor* AGraph::SpawnNodeBP(FString type)
{
	UObject* SpawnActor;
	if (type == "person") SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_GraphNode_person.BP_GraphNode_person")));
	else if (type == "state") SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_GraphNode_state.BP_GraphNode_state")));
	else if (type == "event") SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_GraphNode_event.BP_GraphNode_event")));
	else if (type == "place") SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_GraphNode_place.BP_GraphNode_place")));
	else SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/Blueprints/BP_GraphNode.BP_GraphNode")));
	
	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if (!SpawnActor) {
		UE_LOG(LogTemp, Warning, TEXT("CANT FIND OBJECT TO SPAWN"));
		return NULL;
	}

	UClass* SpawnClass = SpawnActor->StaticClass();
	if (SpawnClass == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("CLASS == NULL"));
		return NULL;
	}

	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	return World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, GetActorLocation(), GetActorRotation(), SpawnParams);

}

// Called every frame
void AGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//for (int32 i = 1; i <= Nodes.Num(); i++) {
	//	if (i == currentId) Nodes[i]->IsCurrent = true; else Nodes[i]->IsCurrent = false;
	//}
}

void AGraph::GenerateLocationForNodes()
{
	for (int32 i = 1; i <= Nodes.Num(); i++) {
		FVector location = Nodes[i]->GenerateLocation();
	}
}


