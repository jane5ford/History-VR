// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphNode.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GraphNodePlace.generated.h"

/**
 * 
 */
UCLASS()
class HISTORYVR_API AGraphNodePlace : public AGraphNode
{
	GENERATED_BODY()
public:
    AGraphNodePlace();

protected:
    UPaperSprite* placeSprite;
};
