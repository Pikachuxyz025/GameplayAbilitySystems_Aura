// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AuraPlayerController.h"
#include "Interfaces/EnemyInterface.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Input/AuraInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext); // it seem like we can use check for the variable in question to see if it's valid 

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if(Subsystem)
	Subsystem->AddMappingContext(AuraContext, 0);

	// setting up cursor in game
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraInput = CastChecked<UAuraInputComponent>(InputComponent);

	AuraInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInput->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);

}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn * ControlledPawn = GetPawn<APawn>())
	{
		// add movement 
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)return;

	FString ActorName = UKismetSystemLibrary::GetDisplayName(CursorHit.GetActor());
	//UE_LOG(LogTemp, Display, TEXT("Hit %s"), *ActorName);
	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor(); // Thanks to TScriptInterface, casting isn't necessary

	/**
	* Line trace for cursor. There are several scenarios:
	*	A. LastActor is null && ThisActor is null
	*		- Do Nothing
	*	B. LastActor is null && ThisActor is valid
	*		- Highlight ThisActor
	*	C. LastActor is valid && ThisActor is null
	*		- UnHighlight LastActor
	*	D. Both Actors are valid but LastActor != ThisActor
	*		- UnHighlight LastActor && Highlight ThisActor
	*	E. Both Actors are valid and are the same actor
	*		- Do Nothing
	*/

	if (ThisActor != LastActor)
	{
		if (LastActor)
		{
			LastActor->UnHighlightActor();
		}
		if(ThisActor)
		{
			ThisActor->HighlightActor();
		}
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Blue, *InputTag.ToString());
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Green, *InputTag.ToString());
}
