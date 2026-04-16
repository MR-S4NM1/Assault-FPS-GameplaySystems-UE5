// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/FPSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/FPSDamageInterface.h"
#include "InputActionValue.h"
#include "Interfaces/FPSInterface.h"
#include "Items/FPSWeapon.h"

AFPSCharacter::AFPSCharacter()
{
 	PrimaryActorTick.bCanEverTick = true;

	FPSCamera = CreateDefaultSubobject<UCameraComponent>("FPSCamera");
	FPSCamera->SetupAttachment(GetRootComponent());

	PlayerMesh = ACharacter::GetMesh();
	PlayerMesh->SetupAttachment(FPSCamera);
	
	// Enum default value
	CurrentWeaponState = EWeaponState::Unarmed;
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// TODO: Write a timer function which casts linetraces by periods of time instead of using the tick for it.
	CustomLineTrace();
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	const APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(FPSMappingContext, 0);
	}

	if (UEnhancedInputComponent* FPSEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		FPSEnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::MoveEnhanced);
		FPSEnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::LookEnhanced);
		FPSEnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		FPSEnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		FPSEnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AFPSCharacter::InteractEnhanced);
		FPSEnhancedInput->BindAction(FireAction, ETriggerEvent::Triggered, this, &AFPSCharacter::FireEnhanced);
	}
}



void AFPSCharacter::MoveEnhanced(const FInputActionValue& Value)
{
	FVector2d MovementVector = Value.Get<FVector2d>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AFPSCharacter::LookEnhanced(const FInputActionValue& Value)
{
	FVector2d LookVector = Value.Get<FVector2d>();
	AddControllerYawInput(LookVector.X * MouseLookUpRate);
	AddControllerPitchInput(LookVector.Y * MouseLookUpRate);
	Pitch = LookVector.Y;
}

void AFPSCharacter::InteractEnhanced(const FInputActionValue& Value)
{
	//CustomLineTrace();
	if (LineTraceHitResult.bBlockingHit)
	{
		if (AActor* HitActor = LineTraceHitResult.GetActor())
		{
			if (IFPSInterface* ImplementedActor = Cast<IFPSInterface>(HitActor))
			{
				ImplementedActor->Execute_PlayerInteract(HitActor);
			}
		}
	}
}

void AFPSCharacter::FireEnhanced(const FInputActionValue& Value)
{
	if (!bHasWeapon) return;

	FVector Start = FPSCamera->GetComponentLocation();
	FVector ForwardVector = FPSCamera->GetForwardVector();
	FVector End = Start + (ForwardVector * 10000.f);

	FHitResult Hit;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Camera,
		Params
	);

	if (bHit)
	{
		AActor* HitActor = Hit.GetActor();
		PlayFireImpactEffects(Hit.ImpactPoint);
		
		if (HitActor && HitActor->Implements<UFPSDamageInterface>())
			IFPSDamageInterface::Execute_ApplyDamage(HitActor, ShootingDamage);
	}
	
	PlayFireEffects();
}

void AFPSCharacter::CustomLineTrace()
{
	AActor* HitActor = LineTraceHitResult.GetActor();
	
	if (IFPSInterface* ImplementedActor = Cast<IFPSInterface>(HitActor))
		CachedHitActor = HitActor;
	else
		PlayerHideText();
	
	FVector Start = FPSCamera->GetComponentLocation();
	FVector End = Start + (FPSCamera->GetComponentRotation().Vector() * Distance);
	
	GetWorld()->LineTraceSingleByChannel(LineTraceHitResult, Start, End, ECC_Visibility);
	
	if (LineTraceHitResult.bBlockingHit)
		PlayerShowText();
	else
		PlayerHideText();
}

void AFPSCharacter::PlayerShowText()
{
	if (AActor* HitActor = LineTraceHitResult.GetActor())
	{
		if (IFPSInterface* ImplementedActor = Cast<IFPSInterface>(HitActor))
			ImplementedActor->Execute_ShowMessage(HitActor);
	}
}

void AFPSCharacter::PlayerHideText()
{
	if (IFPSInterface* ImplementedActor = Cast<IFPSInterface>(CachedHitActor))
		ImplementedActor->Execute_HideMessage(CachedHitActor);
}

void AFPSCharacter::SpawnWeapon()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	
	if (WeaponClass)
	{
		WeaponMesh = GetWorld()->SpawnActor<AFPSWeapon>(
			WeaponClass, 
			FVector::ZeroVector, 
			FRotator::ZeroRotator,
			SpawnParams);
		
		if (WeaponMesh)
		{
			WeaponMesh->AttachToComponent(
				PlayerMesh, 
				FAttachmentTransformRules::SnapToTargetNotIncludingScale,
				FName("WeaponSocket"));
			
			bHasWeapon = true;
			CurrentWeaponState = EWeaponState::Rifle;
		}
	}
}