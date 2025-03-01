// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GraphNode.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GraphNodePerson.generated.h"

/**
 * 
 */
UCLASS()
class HISTORYVR_API AGraphNodePerson : public AGraphNode
{
	GENERATED_BODY()
public:
    AGraphNodePerson();

protected:
    UPaperSprite* personSprite;
};
