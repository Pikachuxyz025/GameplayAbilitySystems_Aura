// Fill out your copyright notice in the Description page of Project Settings.
using namespace UP;
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;

class UAuraInputConfig;
struct FInputActionValue;

UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AAuraPlayerController();

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IA_Move;

	void Move(const FInputActionValue& Value);
	void CursorTrace();
	TScriptInterface<IEnemyInterface>LastActor; // The new way to use pointers particularly for interfaces
	TScriptInterface<IEnemyInterface>ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	//class	 UEnhancedInputLocalPlayerSubsystem* Subsystem;
};
