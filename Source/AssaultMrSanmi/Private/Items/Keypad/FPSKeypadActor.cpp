// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Keypad/FPSKeypadActor.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AFPSKeypadActor::AFPSKeypadActor()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	KeypadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Keypad Mesh"));
	RootComponent = KeypadMesh;
	
	KeypadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Keypad Trigger"));
	KeypadTrigger->SetupAttachment(RootComponent);
	
	KeypadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Keypad Widget"));
	KeypadWidget->SetupAttachment(RootComponent);
}

void AFPSKeypadActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFPSKeypadActor::PlayerInteract_Implementation()
{
	IFPSInterface::PlayerInteract_Implementation();
	// ControlCenterDoorOpener();
}

void AFPSKeypadActor::InternalInteract_Implementation()
{
	IFPSInterface::InternalInteract_Implementation();
	ControlCenterDoorOpener();
}

void AFPSKeypadActor::ControlCenterDoorOpener()
{
	bControlCenterDoorOpened = true;
}

void AFPSKeypadActor::ShowMessage_Implementation()
{
	IFPSInterface::ShowMessage_Implementation();
	
	UUserWidget* Widget = KeypadWidget->GetUserWidgetObject();
		
	if (UFunction* ShowText = Widget->FindFunction("ShowText"))
	{
		Widget->ProcessEvent(ShowText, nullptr);
	}
}

void AFPSKeypadActor::HideMessage_Implementation()
{
	IFPSInterface::HideMessage_Implementation();
	
	UUserWidget* Widget = KeypadWidget->GetUserWidgetObject();
		
	if (UFunction* ShowText = Widget->FindFunction("HideText"))
	{
		Widget->ProcessEvent(ShowText, nullptr);
	}
}
