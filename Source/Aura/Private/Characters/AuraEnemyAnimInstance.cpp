// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AuraEnemyAnimInstance.h"
#include "Characters/AuraEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAuraEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EnemyCharacter = Cast<AAuraEnemy>(TryGetPawnOwner());
	if (EnemyCharacter)
	{
		EnemyCharacterMovement = EnemyCharacter->GetCharacterMovement();
	}
}

void UAuraEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!EnemyCharacter || !EnemyCharacterMovement)return;

	GroundSpeed = UKismetMathLibrary::VSizeXY(EnemyCharacterMovement->Velocity);
	bIsFalling = EnemyCharacterMovement->IsFalling();
}
