#include "HidingSpot.h"
#include "../Player/BugBreakPlayerCharacter.h"
#include "Components/BoxComponent.h"

AHidingSpot::AHidingSpot()
{
	UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(TEXT("HideVolume"));
	Box->SetBoxExtent(FVector(80.f, 80.f, 90.f));
	Box->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = Box;
}

void AHidingSpot::BeginPlay()
{
	Super::BeginPlay();
}

void AHidingSpot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (ABugBreakPlayerCharacter* Player = Cast<ABugBreakPlayerCharacter>(OtherActor))
	{
		Player->SetCanHide(true);
	}
}

void AHidingSpot::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (ABugBreakPlayerCharacter* Player = Cast<ABugBreakPlayerCharacter>(OtherActor))
	{
		Player->SetCanHide(false);
	}
}
