#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BugBreakGameMode.generated.h"

/**
 * ABugBreakGameMode
 * Controls room flow, win/lose logic, and map transitions.
 * Set as the Game Mode in each gameplay level's World Settings.
 */
UCLASS()
class BUGBREAK_API ABugBreakGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Total number of gameplay rooms before the coffee room. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|Rooms")
	int32 TotalRooms = 3;

	/** Map name prefix used to build room level names (e.g. "LV_Room"). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|Rooms")
	FString RoomMapPrefix = TEXT("LV_Room");

	/** Map name for the final coffee room. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|Rooms")
	FString CoffeeRoomMap = TEXT("LV_CoffeeRoom");

	/** Map name for the main menu. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|Rooms")
	FString MainMenuMap = TEXT("LV_MainMenu");

	/**
	 * Loads the next room or the coffee room if all rooms are cleared.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Flow")
	void AdvanceToNextRoom();

	/**
	 * Called when the spider catches the player.
	 * Triggers lose flow and returns to main menu without coffee.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Flow")
	void HandlePlayerCaught();

	/**
	 * Called when the player interacts with the coffee machine.
	 * Triggers win flow and returns to main menu with coffee.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Flow")
	void HandleCoffeeReached();

private:
	/**
	 * Opens the main menu level.
	 * Input:  bWithCoffee — stores coffee state before loading
	 * Output: none
	 */
	void LoadMainMenu(bool bWithCoffee);

	/**
	 * Opens a gameplay room level by room index.
	 * Input:  RoomIndex — zero-based room number
	 * Output: none
	 */
	void LoadRoomByIndex(int32 RoomIndex);
};
