// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Aura/AuraLogChannels.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)
{
#pragma region My Solution	
	/*
	TArray<int32> LevelKeys;
	LevelUpSet.GetKeys(LevelKeys);

	if (LevelKeys.Num() == 0)
	{
		UE_LOG(LogAura, Error, TEXT("TMAP LevelupSet has no content"));
		return 1;
	}

	for (int32 i = 0; i < LevelKeys.Num(); i++)
	{
		if (XP < LevelUpSet[LevelKeys[i]].LevelUpRequirement)
		{
			return LevelKeys[i];
		}
	}
	*/
#pragma endregion

#pragma region Course Solution
	bool bSearching = true;
	int32 Level = 1;
	while (bSearching)
	{
		// LevelUpInformation[1] = Level 1 Information
		// LevelUpInformation[2] = Level 2 Information
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
#pragma endregion
}

FAuraLevelUpInfo ULevelUpInfo::GetLevelUpInfo(int32 CurrentLevel)
{
	if (LevelUpInformation.IsValidIndex(CurrentLevel))
		return LevelUpInformation[CurrentLevel];
	return FAuraLevelUpInfo();
}
