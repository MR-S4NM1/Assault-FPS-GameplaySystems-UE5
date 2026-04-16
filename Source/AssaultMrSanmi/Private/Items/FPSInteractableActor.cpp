// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/FPSInteractableActor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Items/Keypad/FPSKeypadActor.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/FPSInterface.h"

AFPSInteractableActor::AFPSInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = InteractableMesh;
	
	InteractVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Volume"));
	InteractVolume->SetupAttachment(RootComponent);
	
	InteractWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	InteractWidget->SetupAttachment(RootComponent);

}

void AFPSInteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSInteractableActor::PlayerInteract_Implementation()
{
	IFPSInterface::PlayerInteract_Implementation();
	
	if (IFPSInterface* ImplementedActor = Cast<IFPSInterface>(this))
	{
		if (KeypadRef)
		{
			ImplementedActor->Execute_InternalInteract(KeypadRef);
		}
		
		if (BipSound)
		{
			UGameplayStatics::PlaySound2D(this, BipSound);
		}
	}
	
	OnPlayerInteracted.Broadcast();
}

void AFPSInteractableActor::ShowMessage_Implementation()
{
	IFPSInterface::ShowMessage_Implementation();
	
	UUserWidget* Widget = InteractWidget->GetUserWidgetObject();
		
	if (UFunction* ShowText = Widget->FindFunction("ShowText"))
	{
		if (Widget)
		{
			Widget->ProcessEvent(ShowText, nullptr);
		}
	}
}

void AFPSInteractableActor::HideMessage_Implementation()
{
	IFPSInterface::HideMessage_Implementation();
	
	UUserWidget* Widget = InteractWidget->GetUserWidgetObject();
		
	if (UFunction* HideText = Widget->FindFunction("HideText"))
	{
		Widget->ProcessEvent(HideText, nullptr);
	}
}
