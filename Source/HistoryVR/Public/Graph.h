// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <HistoryVR\Public\HistoryEvent.h>
#include "GameFramework/Actor.h"
#include "Graph.generated.h"

UCLASS()
class HISTORYVR_API AGraph : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraph();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<int32, AHistoryEvent*> Nodes;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void CreateRelation(int32 nodeA_id, int32 nodeB_id);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
