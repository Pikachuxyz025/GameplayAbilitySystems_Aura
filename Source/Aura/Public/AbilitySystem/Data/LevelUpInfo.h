// Fill out your copyright notice in the Description page of Project Settings.
using namespace UP;
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointAward = 1;
};

UCLASS(BlueprintType)
class AURA_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
	

public:

	// My Solution
	//UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	//TMap<int32, FAuraLevelUpInfo> LevelUpSet;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FAuraLevelUpInfo> LevelUpInformation;

	UFUNCTION(BlueprintCallable,BlueprintPure)
	int32 FindLevelForXP(int32 XP);

	FAuraLevelUpInfo GetLevelUpInfo(int32 CurrentLevel);
};
