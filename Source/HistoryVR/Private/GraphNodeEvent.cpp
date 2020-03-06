// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNodeEvent.h"

AGraphNodeEvent::AGraphNodeEvent()
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> h_eventSprite(TEXT("PaperSprite'/Game/Sprites/event_Sprite.event_Sprite'"));
	eventSprite = h_eventSprite.Object;
	SpriteComponent->SetSprite(eventSprite);
}
