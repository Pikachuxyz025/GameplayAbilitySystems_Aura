// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Controller/AuraPlayerController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/HUD/AuraHUD.h"
#include "Camera/CameraComponent.h"
#include <Player/AuraPlayerState.h>

AAuraCharacter::AAuraCharacter()
{	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 750.f; // The camera follows at this distance behind the character
	CameraBoom->SocketOffset = FVector(0, 0, 0);
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	CameraBoom->bEnableCameraLag = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

int32 AAuraCharacter::GetPlayerLevel()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init Ability Actor Info for the server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init Ability Actor Info for the client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{	
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();

	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	
	if (AAuraPlayerController* AuraPC = Cast<AAuraPlayerController>(GetController()))
	{
		if(AAuraHUD * AuraHUD = Cast<AAuraHUD>(AuraPC->GetHUD()))
		AuraHUD->InitOverlay(AuraPC, AuraPlayerState, AbilitySystemComponent, AttributeSet);
	}
	InitialDefaultAttributes();
}
