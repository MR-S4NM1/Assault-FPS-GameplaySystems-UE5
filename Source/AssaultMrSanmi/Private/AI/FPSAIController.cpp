// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/FPSAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AFPSAIController::AFPSAIController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception Component");
	SetPerceptionComponent(*AIPerceptionComp);
	
	SightConfig->SightRadius = 1500.f;
	SightConfig->LoseSightRadius = 1600.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	
	AIPerceptionComp->ConfigureSense(*SightConfig);
	AIPerceptionComp->SetDominantSense(UAISense_Sight::StaticClass());
}

void AFPSAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(EnemyBehaviorTree);
}

void AFPSAIController::SetFPSAISightRange(float NewSightRange)
{
	if (AIPerceptionComp && SightConfig)
	{
		SightConfig->SightRadius = NewSightRange;

		AIPerceptionComp->ConfigureSense(*SightConfig);
		AIPerceptionComp->RequestStimuliListenerUpdate();
	}
}
