// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNodePlace.h"

AGraphNodePlace::AGraphNodePlace()
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> h_placeSprite(TEXT("PaperSprite'/Game/Sprites/place_Sprite.place_Sprite'"));
	placeSprite = h_placeSprite.Object;
	SpriteComponent->SetSprite(placeSprite);
}