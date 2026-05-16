#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoomManager.generated.h"

/**
 * ARoomManager
 * Place one of these in each room level.
 * Tracks how many bugged props exist and how many have been found.
 */
UCLASS()
class BUGBREAK_API ARoomManager : public AActor
{
	GENERATED_BODY()

public:
	/** Number of bugged props required to clear this room. Set in editor per level. */
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "BugBreak|Room")
	int32 RequiredBugCount = 3;

	/**
	 * Resets progress and sets the required find count.
	 * Call from BeginPlay of this actor or a level Blueprint.
	 * Input:  InRequiredBugCount — total bugs to find in this room
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Room")
	void InitializeRoom(int32 InRequiredBugCount);

	/**
	 * Increments the found count. Triggers room clear if all bugs found.
	 * Call this from ASwappableActor when the player finds a bug.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Room")
	void RegisterFoundBug();

	/**
	 * Returns whether all required bugs have been found.
	 * Input:  none
	 * Output: bool — true if room is cleared
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|Room")
	bool IsRoomCleared() const;

	/**
	 * Returns the number of bugs found so far.
	 * Input:  none
	 * Output: int32
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|Room")
	int32 GetFoundBugCount() const { return FoundBugCount; }

	/**
	 * Returns the total required bugs for this room.
	 * Input:  none
	 * Output: int32
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|Room")
	int32 GetRequiredBugCount() const { return RequiredBugCount; }

private:
	int32 FoundBugCount = 0;
};
