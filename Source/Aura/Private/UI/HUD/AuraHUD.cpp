// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include"UI/Widget/AuraUserWidget.h"
#include"UI/WidgetController/OverlayWidgetController.h"


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

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{	
	check(OverlayWidgetClass);//, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	check(OverlayWidgetControllerClass);//,TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"))

	UUserWidget*	Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	AuraOverlayWidget = Cast<UAuraUserWidget>(Widget);
	FWidgetControllerParams NewParams = FWidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(NewParams);


	AuraOverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitialValues();

	Widget->AddToViewport();
}
