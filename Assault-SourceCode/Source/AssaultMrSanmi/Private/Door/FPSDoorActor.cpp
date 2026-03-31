#include "Door/FPSDoorActor.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"

AFPSDoorActor::AFPSDoorActor()
{
 	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootSceneComponent;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(RootComponent);
	
	DoorTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Trigger"));
	DoorTrigger->SetupAttachment(RootComponent);
	
	TlDoor = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
}

void AFPSDoorActor::BeginPlay()
{
	Super::BeginPlay();

	DoorInitialLocation = DoorMesh->GetRelativeLocation();
	DoorFinalLocation = DoorInitialLocation + FVector(0.f, 0.f, ZDoorDistance);

	DoorTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFPSDoorActor::OnDoorBeginOverlap);
	DoorTrigger->OnComponentEndOverlap.AddDynamic(this, &AFPSDoorActor::OnDoorEndOverlap);
	
	if (FloatCurve)
	{
		// Bindeamos la curve a la función de Update del Timeline
		FOnTimelineFloat UpdateTl;
		UpdateTl.BindUFunction(this, FName("UpdateTlFunction"));
		
		TlDoor->AddInterpFloat(FloatCurve, UpdateTl);
		TlDoor->SetLooping(false);
	}
}


void AFPSDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TlDoor->TickComponent(DeltaTime, LEVELTICK_TimeOnly, nullptr);
}

void AFPSDoorActor::UpdateTlFunction(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Estoy overlapeando"));
	FVector NewLocation = FMath::Lerp(DoorInitialLocation, DoorFinalLocation, Value);
	DoorMesh->SetRelativeLocation(NewLocation);
}

void AFPSDoorActor::OnDoorBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Display, TEXT("Estoy overlapeando"));

	if ((OtherActor && OtherActor->IsA<APawn>()) && bCanBeOpened)
	{
		TlDoor->Play();
	}
}

void AFPSDoorActor::OnDoorEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Display, TEXT("Estoy saliendo"));
	if ((OtherActor && OtherActor->IsA<APawn>()) && bCanBeOpened)
	{
		TlDoor->Reverse();
	}
}
