// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_TargetDataUnderMouse.h"
#include <Controller/AuraPlayerController.h>

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
		 // TODO: We are on the server
	 }
	 AAuraPlayerController* APC = Cast<AAuraPlayerController>(Ability->GetCurrentActorInfo()->PlayerController.Get());
	 FHitResult CursorHit = APC->GetCursorHit();

	 if (CursorHit.bBlockingHit)
		 ValidData.Broadcast(CursorHit.Location);
 }

 void UAT_TargetDataUnderMouse::SendMouseCursorData()
 {
 }
