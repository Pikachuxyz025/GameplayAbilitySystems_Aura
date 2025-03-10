// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// Mana
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"



			// Description
			"<Default>Launches a bolt of fire, exploding on impact and dealing: </>"
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>\n\n"),
			
			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// Mana
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Description
			"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
			"<Damage>%d</>"
			"<Default> fire damage with a chance to burn</>\n\n"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumOfProjectiles),
			ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		// Title
		"<Title>NEXT LEVEL: </>\n\n"

		// Level
		"<Small>Level: </><Level>%d</>\n"
		// Mana
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		// Cooldown
		"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

		// Description
		"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
		"<Damage>%d</>"
		"<Default> fire damage with a chance to burn</>\n\n"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumOfProjectiles),
		ScaledDamage);
}
