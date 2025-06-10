// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/MagicCircleActor.h"
#include "Components/DecalComponent.h"

// Sets default values
AMagicCircleActor::AMagicCircleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	MagicCircleDecal = CreateDefaultSubobject<UDecalComponent>("MagicCircleDecal");
	MagicCircleDecal->SetupAttachment(GetRootComponent());
}

void AMagicCircleActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMagicCircleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

