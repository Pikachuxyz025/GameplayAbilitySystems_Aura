// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_TargetDataUnderMouse.h"
#include <Controller/AuraPlayerController.h>
#include "AbilitySystemComponent.h"

 UAT_TargetDataUnderMouse* UAT_TargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	 UAT_TargetDataUnderMouse* MyObj = NewAbilityTask<UAT_TargetDataUnderMouse>(OwningAbility);

	 return MyObj;
}

 void UAT_TargetDataUnderMouse::Activate()
 {
	 const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	 if (bIsLocallyControlled)
	 {
		 SendMouseCursorData();
	 }
	 else
	 {
		 const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		 const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();

		 AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UAT_TargetDataUnderMouse::OnTargetDataReplicatedCallback);

		 const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey);
		 if (!bCalledDelegate)
		 {
			 SetWaitingOnRemotePlayerData();
		 }
	 }
 }

 void UAT_TargetDataUnderMouse::SendMouseCursorData()
 {
	 FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	 FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	 FGameplayAbilityTargetDataHandle DataHandle;

	 AAuraPlayerController* APC = Cast<AAuraPlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get());
	 FHitResult CursorHit = APC->GetCursorHit();
	
	 Data->HitResult = CursorHit;
	 DataHandle.Add(Data);

	 AbilitySystemComponent->ServerSetReplicatedTargetData(
		 GetAbilitySpecHandle(),
		 GetActivationPredictionKey(),
		 DataHandle,
		 FGameplayTag(),
		 AbilitySystemComponent->ScopedPredictionKey);

	 if (ShouldBroadcastAbilityTaskDelegates())
	 {
		 ValidData.Broadcast(DataHandle);
	 }
 }

 void UAT_TargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
 {
	 AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	
	 if (ShouldBroadcastAbilityTaskDelegates())
	 {
		 ValidData.Broadcast(DataHandle);
	 }
 }
