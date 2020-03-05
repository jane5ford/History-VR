// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph.h"
#include "HistoryEvent.h"
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
}

// Called when the game starts or when spawned
void AGraph::BeginPlay()
{
	Super::BeginPlay();

	FString directory2 = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + NodesData;
	TArray<FString> nodesArray;
	if (FFileHelper::LoadFileToStringArray(nodesArray, *directory2)) {
		int32 k = 0;
			FString res;
			FString res1, res2;
			AHistoryEvent* node;
			for (int32 i = 1; i <= 10; i++) {
				node = GetWorld()->SpawnActor<AHistoryEvent>(FVector(-60.f, 0.f, 120.f), FRotator(0.f, 0.f, 0.f));
				nodesArray[k].Split(":", &res1, &res2);
				node->SetDescription(res2);
				node->SetDate(nodesArray[k + 1]);
				node->SetType(res1);				
				node->Create(i);
				Nodes.Add(i, node);
				k = k + 2;
			}
	}
	else UKismetSystemLibrary::PrintString(this, "File Not Found", true, true, FLinearColor(0, 0, 0, 1), 100.f);

	FString directory = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + AdjacencyList;
	TArray<FString> adjacencyArray;
	if (FFileHelper::LoadFileToStringArray(adjacencyArray, *directory)) {
		//FString IntAsString = FString::FromInt();
		//UKismetSystemLibrary::PrintString(this, "Nodes and Edges: " + result[0], true, true, FLinearColor(0, 0, 0, 1), 100.f);
		FString res;
		FString res1, res2;
		for (int32 i = 1; i < adjacencyArray.Num(); i++) {
			res = adjacencyArray[i];
			res.Split(" ", &res1, &res2);
			//UKismetSystemLibrary::PrintString(this, res1 + " " + res2, true, true, FLinearColor(0, 0, 0, 1), 100.f);
			int32 nodeA_id = FCString::Atoi(*res1);
			int32 nodeB_id = FCString::Atoi(*res2);
			CreateRelation(nodeA_id, nodeB_id);
		}
	}
	else UKismetSystemLibrary::PrintString(this, "File Not Found", true, true, FLinearColor(0, 0, 0, 1), 100.f);
}

void AGraph::CreateRelation(int32 nodeA_id, int32 nodeB_id) {

	AHistoryEvent* nodeA;
	AHistoryEvent* nodeB;
	nodeA = Nodes[nodeA_id];
	nodeB = Nodes[nodeB_id];
	AHistoryEdge* edge = GetWorld()->SpawnActor<AHistoryEdge>();
	edge->Create(nodeA, nodeB);
}

// Called every frame
void AGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int32 i = 1; i <= Nodes.Num(); i++) {
		if (i == currentId) Nodes[i]->IsCurrent = true; else Nodes[i]->IsCurrent = false;
	}
}