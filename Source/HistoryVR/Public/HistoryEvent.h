// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "PaperSpriteComponent.h"
#include "HistoryEvent.generated.h"

UCLASS()
class HISTORYVR_API AHistoryEvent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHistoryEvent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
		int32 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Date;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Type;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* PS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* TextDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* TextDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* NodeMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* NodeSceneComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Create(int32 id);
	void SetDescription(FString description);
	void SetDate(FString date);
	void SetType(FString type);
};