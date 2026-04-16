// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssaultMrSanmiGameMode.h"
#include "AssaultMrSanmiCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAssaultMrSanmiGameMode::AAssaultMrSanmiGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
