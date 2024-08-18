// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AuraInputConfig.h"
#include "InputActionValue.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for InputTag [%s] on Input [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
