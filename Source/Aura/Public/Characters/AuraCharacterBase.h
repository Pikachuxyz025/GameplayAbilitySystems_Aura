// Fill out your copyright notice in the Description page of Project Settings.
using namespace UP;
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interfaces/CombatInterface.h"
#include "AbilitySystemInterface.h"
#include "AuraCharacterBase.generated.h"

class UGameplayEffect;
class UGameplayAbility;
class UAnimMontage;
class UNiagaraSystem;
class UDebuffNiagaraComponent;
class UPassiveNiagaraComponent;

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(const FVector& DeathImpulse);

#pragma region Combat Interface

	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual bool IsBeingShocked_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetAttackMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void SetMinionCount_Implementation(int32 Amount) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	virtual FOnASCRegistered& GetOnASCRegisteredDelegate() override;
	virtual FOnDeathDelegate& GetOnDeathDelegate() override;
	virtual USkeletalMeshComponent* GetWeapon_Implementation() override;
	virtual void SetIsBeingShocked_Implementation(bool bInShock) override;
	FOnASCRegistered OnAscRegistered;
	FOnDeathDelegate OnDeath;
	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<FTaggedMontage> AttackMontages;
#pragma endregion

	UPROPERTY(ReplicatedUsing=OnRep_Stunned,BlueprintReadOnly)
	bool bIsStunned = false;

	UPROPERTY(ReplicatedUsing=OnRep_Burned,BlueprintReadOnly)
	bool bIsBurned = false;

	UPROPERTY(Replicated,BlueprintReadOnly)
	bool bIsBeingShocked = false;

	UFUNCTION()
	virtual void OnRep_Stunned();

	UFUNCTION()
	virtual void OnRep_Burned();
protected:

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 600.f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName TailSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TMap<FGameplayTag, FName> TagsToSocketNames;

	bool bDead = false;

	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<class UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	// Inherited via IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual void InitAbilityActorInfo();

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;

	void AddCharacterAbilities();

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	// Dynamic instance that we can change at runtime
	UPROPERTY(VisibleAnywhere, Category = "Elim")
	TObjectPtr<UMaterialInstanceDynamic> DynamicDissolveMaterialInstance;

	// Material instance set on the Blueprint, used with the dynamic material instance
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elim")
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Elim")
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* BloodEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* DeathSound;

	/* Minions */

	int32 MinionCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent> BurnDebuffComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent> StunDebuffComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPassiveNiagaraComponent> HaloOfProtectionComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPassiveNiagaraComponent> LifeSiphonComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPassiveNiagaraComponent> ManaSiphonComponent;

	TObjectPtr<USceneComponent> EffectAttachComponent;

private:

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
