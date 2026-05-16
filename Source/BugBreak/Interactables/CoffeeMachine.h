#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoffeeMachine.generated.h"

class ABugBreakPlayerCharacter;

/**
 * ACoffeeMachine
 * The final win-state interactable. Place one in the coffee room.
 * When the player interacts with it, the win sequence triggers.
 */
UCLASS()
class BUGBREAK_API ACoffeeMachine : public AActor
{
	GENERATED_BODY()

public:
	ACoffeeMachine();

	/**
	 * Triggers the win sequence when the player interacts.
	 * Calls GameMode->HandleCoffeeReached().
	 * Input:  InteractingPlayer — the player using the machine
	 * Output: bool — true if the interaction succeeded
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Flow")
	bool Interact(ABugBreakPlayerCharacter* InteractingPlayer);
};
