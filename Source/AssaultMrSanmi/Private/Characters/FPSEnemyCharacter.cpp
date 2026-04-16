// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/FPSEnemyCharacter.h"

void AFPSEnemyCharacter::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	Super::GetActorEyesViewPoint(OutLocation, OutRotation);
	/*OutLocation = GetMesh()->GetSocketLocation(TEXT("AISocket"));
	OutRotation = GetMesh()->GetSocketRotation(TEXT("AISocket"));*/
}
