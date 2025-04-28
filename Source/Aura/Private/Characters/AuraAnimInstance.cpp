// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AuraAnimInstance.h"
#include "Characters/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAuraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	AuraCharacter = Cast<AAuraCharacter>(TryGetPawnOwner());
	if (AuraCharacter)
	{
		AuraCharacterMovement = AuraCharacter->GetCharacterMovement();
	}
}

void UAuraAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!AuraCharacter || !AuraCharacterMovement)return;

	GroundSpeed = UKismetMathLibrary::VSizeXY(AuraCharacterMovement->Velocity);
	bShouldMove = GroundSpeed > 3.f;
	bIsFalling = AuraCharacterMovement->IsFalling();

	bInShockLoop = AuraCharacter->bInShockLoop;
}
