#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BugBreakGameInstance.generated.h"

/**
 * UBugBreakGameInstance
 * Persists run-wide state across map loads (coffee, room index, ending).
 * Assigned as the Game Instance class in Project Settings.
 */
UCLASS()
class BUGBREAK_API UBugBreakGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/**
	 * Resets all run state to defaults.
	 * Call this at the start of a new run from the main menu.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Run")
	void ResetRunState();

	/**
	 * Stores whether the player finished the run with coffee.
	 * Input:  bInHasCoffee — true if player reached the coffee machine
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Run")
	void SetHasCoffee(bool bInHasCoffee);

	/**
	 * Returns whether the player currently has coffee.
	 * Input:  none
	 * Output: bool — true if player won with coffee
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|Run")
	bool GetHasCoffee() const { return bHasCoffee; }

	/**
	 * Stores the current room progression index.
	 * Input:  InRoomIndex — zero-based room number
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Run")
	void SetCurrentRoomIndex(int32 InRoomIndex);

	/**
	 * Returns the current room index.
	 * Input:  none
	 * Output: int32 — current room number
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|Run")
	int32 GetCurrentRoomIndex() const { return CurrentRoomIndex; }

private:
	UPROPERTY()
	bool bHasCoffee = false;

	UPROPERTY()
	int32 CurrentRoomIndex = 0;
};
