#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidgetBase.generated.h"

/**
 * UMainMenuWidgetBase
 * Base C++ class for the main menu widget.
 * Create a Blueprint child WBP_MainMenu and design the UI there.
 * Use GetHasCoffee() from the GameInstance to show the right ending state.
 */
UCLASS(Abstract)
class BUGBREAK_API UMainMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * Returns whether the player has coffee (from the GameInstance).
	 * Use this in Blueprint to toggle coffee / no-coffee visuals.
	 * Input:  none
	 * Output: bool
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|UI")
	bool GetHasCoffee() const;

	/**
	 * Starts a new run. Resets GameInstance state and opens the first room.
	 * Bind this to your Start button's OnClicked event in Blueprint.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|UI")
	void StartNewRun();

	/**
	 * Quits the game.
	 * Bind this to your Quit button's OnClicked event in Blueprint.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|UI")
	void QuitGame();
};
