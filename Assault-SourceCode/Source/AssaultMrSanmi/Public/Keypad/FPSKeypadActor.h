// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSInterface.h"
#include "GameFramework/Actor.h"
#include "FPSKeypadActor.generated.h"

class UWidgetComponent;
class UBoxComponent;

UCLASS()
class ASSAULTMRSANMI_API AFPSKeypadActor : public AActor, public IFPSInterface
{
	GENERATED_BODY()
	
public:	
	AFPSKeypadActor();
	
	// Interface Implementation
	virtual void PlayerInteract_Implementation() override;
	virtual void InternalInteract_Implementation() override;
	virtual void ShowMessage_Implementation() override;
	virtual void HideMessage_Implementation() override;

protected:
	virtual void BeginPlay() override;

private:
	// Variables
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* KeypadMesh;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBoxComponent* KeypadTrigger;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UWidgetComponent* KeypadWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bControlCenterDoorOpened { false };
	
	// Functions
	void ControlCenterDoorOpener();
	
	// Overrides

};
