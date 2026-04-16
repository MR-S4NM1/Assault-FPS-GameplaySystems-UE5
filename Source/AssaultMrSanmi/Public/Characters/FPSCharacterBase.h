// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/FPSDamageInterface.h"
#include "GameFramework/Character.h"
#include "FPSCharacterBase.generated.h"

UCLASS()
class ASSAULTMRSANMI_API AFPSCharacterBase : public ACharacter, public IFPSDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacterBase();
	
	// Interface methods
	virtual void ApplyDamage_Implementation(float DamageAmount) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
