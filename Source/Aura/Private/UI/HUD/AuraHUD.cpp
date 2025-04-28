// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include"UI/Widget/AuraUserWidget.h"
#include"UI/WidgetController/OverlayWidgetController.h"
#include"UI/WidgetController/AttributeMenuWidgetController.h"
#include"UI/WidgetController/SpellMenuWidgetController.h"


UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!AttributeMenuWidgetController)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

USpellMenuWidgetController* AAuraHUD::GetSpellMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (!SpellMenuWidgetController)
	{
		SpellMenuWidgetController = NewObject<USpellMenuWidgetController>(this, SpellMenuWidgetControllerClass);
		SpellMenuWidgetController->SetWidgetControllerParams(WCParams);
		SpellMenuWidgetController->BindCallbacksToDependencies();
	}
	return SpellMenuWidgetController;
}

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{	
	check(OverlayWidgetClass);//, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	check(OverlayWidgetControllerClass);//,TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"))

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	AuraOverlayWidget = Cast<UAuraUserWidget>(Widget);
	FWidgetControllerParams NewParams = FWidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(NewParams);


	AuraOverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}
