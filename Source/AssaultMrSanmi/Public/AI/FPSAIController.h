// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPSAIController.generated.h"

class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class ASSAULTMRSANMI_API AFPSAIController : public AAIController
{
	GENERATED_BODY()
	
	AFPSAIController();
	
public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "AI Perception")
	void SetFPSAISightRange(float NewSightRange);
	
public:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
	UAIPerceptionComponent* AIPerceptionComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
	UAISenseConfig_Sight* SightConfig;*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
	UAIPerceptionComponent* AIPerceptionComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Perception")
	UAISenseConfig_Sight* SightConfig;
	
	UPROPERTY(EditAnywhere, Category = "AI")
	UBehaviorTree* EnemyBehaviorTree;
};
