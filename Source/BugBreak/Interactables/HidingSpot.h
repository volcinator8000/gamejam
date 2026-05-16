#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HidingSpot.generated.h"

/**
 * AHidingSpot
 * An invisible volume the player can enter to hide from the spider.
 * Add a BoxComponent or SphereComponent as root in the Blueprint child.
 */
UCLASS()
class BUGBREAK_API AHidingSpot : public AActor
{
	GENERATED_BODY()

public:
	AHidingSpot();

	virtual void BeginPlay() override;

	/**
	 * Called when any actor enters the hiding volume.
	 * If the actor is the player, enables hide ability.
	 * Input:  OtherActor — the actor that entered
	 * Output: none
	 */
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	/**
	 * Called when any actor leaves the hiding volume.
	 * If the actor is the player, disables hide ability.
	 * Input:  OtherActor — the actor that left
	 * Output: none
	 */
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
