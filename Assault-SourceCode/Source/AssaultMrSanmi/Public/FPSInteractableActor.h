// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSInterface.h"
#include "GameFramework/Actor.h"
#include "FPSInteractableActor.generated.h"

class AFPSKeypadActor;
class UWidgetComponent;
class UBoxComponent;

UCLASS()
class ASSAULTMRSANMI_API AFPSInteractableActor : public AActor, public IFPSInterface
{
	GENERATED_BODY()
	
public:	
	AFPSInteractableActor();
	
	// Interface function
	virtual void PlayerInteract_Implementation() override;
	virtual void ShowMessage_Implementation() override;
	virtual void HideMessage_Implementation() override;
	
	// Reference to keypad
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFPSKeypadActor* KeypadRef;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	USoundBase* BipSound;
	
private:
	// Variables
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* InteractableMesh;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UBoxComponent* InteractVolume;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UWidgetComponent* InteractWidget;
	
	// Functions
};
