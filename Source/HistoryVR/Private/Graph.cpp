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
	FString directory = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + AdjacencyList;
	TArray<FString> result;
	if (FFileHelper::LoadFileToStringArray(result, *directory)) {
		//FString IntAsString = FString::FromInt();
		//UKismetSystemLibrary::PrintString(this, "Nodes and Edges: " + result[0], true, true, FLinearColor(0, 0, 0, 1), 100.f);
		FString res;
		FString res1, res2;
		for (int32 i = 1; i < result.Num(); i++) {
			res = result[i];
			res.Split(" ", &res1, &res2);
			//UKismetSystemLibrary::PrintString(this, res1 + " " + res2, true, true, FLinearColor(0, 0, 0, 1), 100.f);
			int32 nodeA_id = FCString::Atoi(*res1);
			int32 nodeB_id = FCString::Atoi(*res2);
			CreateRelation(nodeA_id, nodeB_id);
		}
	}
	else UKismetSystemLibrary::PrintString(this, "File Not Found", true, true, FLinearColor(0, 0, 0, 1), 100.f);

	FString directory2 = FPaths::ConvertRelativePathToFull(FPaths::GameContentDir()) + NodesData;
	TArray<FString> result2;
	if (FFileHelper::LoadFileToStringArray(result2, *directory2)) {
		int32 k = 0;
		if (Nodes.Num() * 2 ==  result2.Num())
			for (int32 i = 1; i <= Nodes.Num(); i++) {
				Nodes[i]->SetDescription(result2[k]);
				Nodes[i]->SetDate(result2[k+1]);
				k=k+2;
			}
	}
	else UKismetSystemLibrary::PrintString(this, "File Not Found", true, true, FLinearColor(0, 0, 0, 1), 100.f);
}

void AGraph::CreateRelation(int32 nodeA_id, int32 nodeB_id) {

	AHistoryEvent* nodeA;
	AHistoryEvent* nodeB;
	if (Nodes.Contains(nodeA_id)) {
		nodeA = Nodes[nodeA_id];
	}
	else {
		nodeA = GetWorld()->SpawnActor<AHistoryEvent>(FVector(-60.f, 0.f, 120.f), FRotator(0.f, 0.f, 0.f));
		nodeA->Create(nodeA_id);
		Nodes.Add(nodeA_id, nodeA);
	}
	if (Nodes.Contains(nodeB_id)) {
		nodeB = Nodes[nodeB_id];
	}
	else {
		nodeB = GetWorld()->SpawnActor<AHistoryEvent>(FVector(-60.f, 0.f, 120.f), FRotator(0.f, 0.f, 0.f));
		nodeB->Create(nodeB_id);
		Nodes.Add(nodeB_id, nodeB);
	}
	AHistoryEdge* edge = GetWorld()->SpawnActor<AHistoryEdge>();
	edge->Create(nodeA, nodeB);
	
	
}



// Called every frame
void AGraph::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

