// Fill out your copyright notice in the Description page of Project Settings.
using namespace UP;
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GameplayModMagnitudeCalculation.h"
#include "Interfaces/ModifierDependencyInterface.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"

class ULevelUpInfo;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChanged, int32 /*StatValue*/);

UCLASS()
class AURA_API AAuraPlayerState : public APlayerState,public IAbilitySystemInterface,public IModifierDependencyInterface
{
	GENERATED_BODY()
	
public:
	AAuraPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FOnPlayerStatChanged OnXPChangedDelegate;
	FOnPlayerStatChanged OnLevelChangedDelegate;
	FOnPlayerStatChanged OnAttributePointChangedDelegate;
	FOnPlayerStatChanged OnSpellPointsChangedDelegate;
	FOnExternalGameplayModifierDependencyChange OnModifierDependencyChanged;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<ULevelUpInfo> LevelUpInfo;
protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;

private: 
	UPROPERTY(VisibleAnywhere,ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_XP)
	int32 XP = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_AttributePoints)
	int32 AttributePoints = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpellPoints)
	int32 SpellPoints = 0;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);

	UFUNCTION()
	void OnRep_AttributePoints(int32 OldAttributePoints);

	UFUNCTION()
	void OnRep_SpellPoints(int32 OldSpellPoints);

public:

	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void SetToXP(int32 InXP);
	void SetToLevel(int32 InLevel);
	void SetToAttributePoints(int32 InAttributePoints);
	void SetToSpellPoints(int32 InSpellPoints);
	void AddToXP(int32 InXP);
	void AddToAttributePoints(int32 InAttributePoints);
	void AddToSpellPoints(int32 InSpellPoints);
	void AddToLevel(int32 InLevel);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE	int32 GetPlayerLevel() const { return Level; }
	FORCEINLINE	int32 GetXP() const { return XP; }
	FORCEINLINE	int32 GetAttributePoints() const { return AttributePoints; }
	FORCEINLINE	int32 GetSpellPoints() const { return SpellPoints; }
	FORCEINLINE virtual FOnExternalGameplayModifierDependencyChange* GetOnModifierDependencyChanged() override { return &OnModifierDependencyChanged; }
};
