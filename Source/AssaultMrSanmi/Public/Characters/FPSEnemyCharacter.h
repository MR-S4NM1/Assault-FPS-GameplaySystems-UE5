// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacterBase.h"
#include "FPSEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ASSAULTMRSANMI_API AFPSEnemyCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()
	
public:
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;
};
