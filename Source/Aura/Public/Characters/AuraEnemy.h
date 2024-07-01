// Fill out your copyright notice in the Description page of Project Settings.
using namespace UP;
#pragma once

#include "CoreMinimal.h"
#include "Characters/AuraCharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase,public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();

#pragma region HighlightInterface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
#pragma endregion

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
};
