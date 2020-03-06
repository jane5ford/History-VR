// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphNodePerson.h"

AGraphNodePerson::AGraphNodePerson() 
{
	ConstructorHelpers::FObjectFinder<UPaperSprite> h_personSprite(TEXT("PaperSprite'/Game/Sprites/person_Sprite.person_Sprite'"));
	personSprite = h_personSprite.Object;
	SpriteComponent->SetSprite(personSprite);
}
