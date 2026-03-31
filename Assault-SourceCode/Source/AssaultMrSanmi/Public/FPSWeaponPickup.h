// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSInteractableActor.h"
#include "FPSWeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class ASSAULTMRSANMI_API AFPSWeaponPickup : public AFPSInteractableActor
{
	GENERATED_BODY()
	
public:
	// Variables
	UPROPERTY(editAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;
	
	// Functions
	AFPSWeaponPickup();
	
	// Overrides
	virtual void PlayerInteract_Implementation() override;
};
