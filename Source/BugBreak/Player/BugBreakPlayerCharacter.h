#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BugBreakPlayerCharacter.generated.h"

/**
 * ABugBreakPlayerCharacter
 * The player pawn. Handles top-down movement, interaction, and hiding.
 * Create a Blueprint child BP_PlayerCharacter and assign meshes/camera there.
 */
UCLASS()
class BUGBREAK_API ABugBreakPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABugBreakPlayerCharacter();

	/** Movement speed in cm/s. Tune in Blueprint child. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|Movement")
	float MoveSpeed = 400.f;

	/**
	 * Binds input actions and axes.
	 * Called automatically by Unreal when this pawn is possessed.
	 * Input:  PlayerInputComponent — the input component assigned to this pawn
	 * Output: none
	 */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/**
	 * Moves the character forward or backward.
	 * Bound to the MoveForward axis.
	 * Input:  Value — positive = forward, negative = backward
	 * Output: none
	 */
	void MoveForward(float Value);

	/**
	 * Moves the character right or left.
	 * Bound to the MoveRight axis.
	 * Input:  Value — positive = right, negative = left
	 * Output: none
	 */
	void MoveRight(float Value);

	/**
	 * Attempts to interact with the closest interactable actor in range.
	 * Bound to the Interact action.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Interaction")
	void Interact();

	/**
	 * Enters hiding state if currently inside a valid HidingSpot.
	 * Bound to the Hide action.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Hiding")
	void BeginHide();

	/**
	 * Exits hiding state.
	 * Bound to the Hide action (toggle).
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Hiding")
	void EndHide();

	/**
	 * Called by AHidingSpot overlap to enable or disable hide ability.
	 * Input:  bInCanHide — true when inside a hiding spot, false when leaving
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Hiding")
	void SetCanHide(bool bInCanHide);

	/**
	 * Returns whether the player is currently hidden.
	 * Used by the spider AI to decide whether to chase or search.
	 * Input:  none
	 * Output: bool
	 */
	UFUNCTION(BlueprintPure, Category = "BugBreak|Hiding")
	bool IsHiddenState() const { return bIsHidden; }

	/**
	 * Called by SpiderAICharacter when it catches the player.
	 * Notifies the GameMode to trigger the lose flow.
	 * Input:  none
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|Flow")
	void Die();

	/** The currently focused interactable (set by overlap). */
	UPROPERTY()
	AActor* FocusedInteractable = nullptr;

private:
	bool bCanHide = false;
	bool bIsHidden = false;
};
