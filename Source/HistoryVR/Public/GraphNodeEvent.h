// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphNode.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GraphNodeEvent.generated.h"

/**
 * 
 */
UCLASS()
class HISTORYVR_API AGraphNodeEvent : public AGraphNode
{
	GENERATED_BODY()
public:
    AGraphNodeEvent();

protected:
    UPaperSprite* eventSprite;
};
