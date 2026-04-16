// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacterBase.h"
#include "FPSCharacter.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	Unarmed UMETA(DisplayName = "Unarmed"),
	Rifle UMETA(DisplayName = "Rifle"),
};

struct FInputActionValue;
class AFPSWeapon;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class ASSAULTMRSANMI_API AFPSCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()

public:
	AFPSCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float Pitch;
	
	UPROPERTY(BlueprintReadOnly)
	EWeaponState CurrentWeaponState;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* FPSMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* FireAction;

	UFUNCTION()
	void MoveEnhanced(const FInputActionValue& Value);

	UFUNCTION()
	void LookEnhanced(const FInputActionValue& Value);
	
	UFUNCTION()
	void InteractEnhanced(const FInputActionValue& Value);
	
	UFUNCTION()
	void FireEnhanced(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayFireEffects();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayFireImpactEffects(FVector Location);
	
	UPROPERTY()
	AFPSWeapon* WeaponMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AFPSWeapon> WeaponClass;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess=true))
	UCameraComponent* FPSCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess=true))
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float MouseLookUpRate = 1.f ;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float Distance = 200.f;
	
	bool bHasWeapon = false;
	
	UFUNCTION()
	void CustomLineTrace();
	
	UFUNCTION()
	void PlayerShowText();
	
	UFUNCTION()
	void PlayerHideText();
	
	FHitResult LineTraceHitResult;
	
	UPROPERTY()
	AActor* CachedHitActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float ShootingDamage = 10.f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void SpawnWeapon();
};
