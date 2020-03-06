// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNodeState.h"

AGraphNodeState::AGraphNodeState()
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> h_stateSprite(TEXT("PaperSprite'/Game/Sprites/state_Sprite.state_Sprite'"));
	stateSprite = h_stateSprite.Object;
	SpriteComponent->SetSprite(stateSprite);
}
