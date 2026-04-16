// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/FPSWeaponPickup.h"
#include "Characters/FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

AFPSWeaponPickup::AFPSWeaponPickup()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(GetRootComponent());
}

void AFPSWeaponPickup::PlayerInteract_Implementation()
{
	Super::PlayerInteract_Implementation();
	
	if (BipSound)
	{
		UGameplayStatics::PlaySound2D(this, BipSound);
	}
	
	if (AFPSCharacter* PlayerRed = Cast<AFPSCharacter>(
		UGameplayStatics::GetPlayerCharacter(
			this, 0)))
	{
		PlayerRed->SpawnWeapon();
	}
	
	Destroy();
}
