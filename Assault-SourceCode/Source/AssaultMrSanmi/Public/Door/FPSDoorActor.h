#pragma once

#include "CoreMinimal.h"
#include "FPSInterface.h"
#include "GameFramework/Actor.h"
#include "FPSDoorActor.generated.h"

class UTimelineComponent;
class UBoxComponent;

UCLASS()
class ASSAULTMRSANMI_API AFPSDoorActor : public AActor, public IFPSInterface
{
	GENERATED_BODY()
	
public:	
	AFPSDoorActor();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UTimelineComponent* TlDoor;

	UPROPERTY(EditAnywhere)
	UCurveFloat* FloatCurve;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZDoorDistance { 450.f };

	UFUNCTION()
	void UpdateTlFunction(float Value);

	UFUNCTION()
	void OnDoorBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);

	UFUNCTION()
	void OnDoorEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

private:
	FVector DoorInitialLocation { 0.f, 0.f, 0.f };
	FVector DoorFinalLocation { 0.f, 0.f, 0.f };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBoxComponent* DoorTrigger;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* RootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool bCanBeOpened { false };
};
