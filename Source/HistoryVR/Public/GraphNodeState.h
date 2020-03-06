// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphNode.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GraphNodeState.generated.h"

/**
 * 
 */
UCLASS()
class HISTORYVR_API AGraphNodeState : public AGraphNode
{
	GENERATED_BODY()
public:
    AGraphNodeState();

protected:
    UPaperSprite* stateSprite;
};
