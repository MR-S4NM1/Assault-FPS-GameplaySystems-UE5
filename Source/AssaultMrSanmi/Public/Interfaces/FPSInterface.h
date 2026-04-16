// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFPSInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ASSAULTMRSANMI_API IFPSInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerInteract();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InternalInteract();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowMessage();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideMessage();
};