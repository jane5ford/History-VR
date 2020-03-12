// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphNode.h"
#include "Graph.generated.h"

UCLASS()
class HISTORYVR_API AGraph : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AGraph();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* NodeSceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString NodesData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<int32, AGraphNode*> Nodes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 currentId = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsRandom;
	UFUNCTION() AGraphNode* SpawnNode(FString type);
	UFUNCTION() AActor* SpawnNodeBP(FString type);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnRelation(int32 nodeA_id, int32 nodeB_id);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

UENUM()
enum NodeType {
	person UMETA(DisplayName = "person"),
	event UMETA(DisplayName = "event"),
	state UMETA(DisplayName = "state"),
	place UMETA(DisplayName = "place")
};
