// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <HistoryVR\Public\HistoryEvent.h>
#include "HistoryEdge.generated.h"



UCLASS()
class HISTORYVR_API AHistoryEdge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHistoryEdge();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Edge_Len;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AHistoryEvent* NodeA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AHistoryEvent* NodeB;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	//	UStaticMeshComponent* NodeMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* NodeSceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* PS;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Create(AHistoryEvent* nodeA, AHistoryEvent* nodeB);
};
