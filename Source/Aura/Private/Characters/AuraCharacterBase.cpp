#include "Characters/AuraCharacterBase.h"
#include "AbilitySystemComponent.h"

AAuraCharacterBase::AAuraCharacterBase()
{

	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);


}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAuraCharacterBase::InitAbilityActorInfo()
{
}

void AAuraCharacterBase::InitializeSecondaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultSecondaryAttributes);

	SetupSpecs(DefaultSecondaryAttributes);
	//const FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	//const FGameplayEffectSpecHandle SpecsHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultSecondaryAttributes, 1.f, EffectContext);
	//FActiveGameplayEffectHandle ActiveEffectHandle = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecsHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::SetupSpecs(TSubclassOf<UGameplayEffect> DefaultAttibutes) const
{
	const FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecsHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultAttibutes, 1.f, EffectContext);
	FActiveGameplayEffectHandle ActiveEffectHandle = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecsHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAuraCharacterBase::InitializePrimaryAttributes() const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(DefaultPrimaryAttributes);

	SetupSpecs(DefaultPrimaryAttributes);
	//const FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	//const FGameplayEffectSpecHandle SpecsHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultPrimaryAttributes, 1.f, EffectContext);
	//FActiveGameplayEffectHandle ActiveEffectHandle = GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecsHandle.Data.Get(), GetAbilitySystemComponent());
}

