// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GraphNode.generated.h"

UCLASS()
class HISTORYVR_API AGraphNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraphNode();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = "true"))
		int32 Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Date;
	bool IsCurrent;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* P_OrangeEllipse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* P_Sparkles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* TextDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UTextRenderComponent* TextDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* NodeSceneComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Locate(int32 id, int32 total, bool random);
	void SetData(FString description, FString date);
};

