#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwappableActor.generated.h"

class ABugBreakPlayerCharacter;

/**
 * ASwappableActor
 * An office prop that may secretly be one of the bugged assets.
 * Place in the level, assign meshes, and check bIsBugged in the editor for the hidden ones.
 * Create a Blueprint child BP_SwappableActor for mesh and effect assignment.
 */
UCLASS()
class BUGBREAK_API ASwappableActor : public AActor
{
	GENERATED_BODY()

public:
	ASwappableActor();

	/** The normal office version of the mesh. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|Swap")
	UStaticMesh* NormalMesh = nullptr;

	/** The bug-swapped version of the mesh. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|Swap")
	UStaticMesh* BuggedMesh = nullptr;

	/** Set to true in the editor for props the player must find. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "BugBreak|Swap")
	bool bIsBugged = false;

	virtual void BeginPlay() override;

	/**
	 * Called when the player presses Interact while focused on this actor.
	 * Returns true if this was a new bugged find. Notifies RoomManager.
	 * Input:  InteractingPlayer — the player interacting
	 * Output: bool — true if the bug was found for the first time
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Swap")
	bool Interact(ABugBreakPlayerCharacter* InteractingPlayer);

	/**
	 * Returns whether this prop is a required bugged asset.
	 * Input:  none
	 * Output: bool
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|Swap")
	bool IsBugged() const { return bIsBugged; }

	/**
	 * Returns whether this bugged prop has already been discovered.
	 * Input:  none
	 * Output: bool
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|Swap")
	bool WasFound() const { return bWasFound; }

private:
	UStaticMeshComponent* MeshComp = nullptr;
	bool bWasFound = false;
};
