#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpiderAICharacter.generated.h"

class ABugBreakPlayerCharacter;
class UNavigationSystemV1;

/**
 * ASpiderAICharacter
 * The enemy. Uses a simple WANDER > CHASE > SEARCH state machine.
 * Create a Blueprint child BP_SpiderAICharacter and assign a mesh + AI Controller.
 */
UCLASS()
class BUGBREAK_API ASpiderAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpiderAICharacter();

	/** Movement speed while wandering. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|AI")
	float WanderSpeed = 200.f;

	/** Movement speed while chasing the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|AI")
	float ChaseSpeed = 450.f;

	/** Radius within which the spider detects the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|AI")
	float DetectionRadius = 800.f;

	/** Distance at which the spider catches the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|AI")
	float CatchRadius = 80.f;

	/** How long the spider searches after losing the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BugBreak|AI")
	float SearchDuration = 3.f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * Assigns the player reference used by chase and detection logic.
	 * Input:  InPlayer — the player character actor
	 * Output: none
	 */
	UFUNCTION(BlueprintCallable, Category = "BugBreak|AI")
	void SetTargetPlayer(ABugBreakPlayerCharacter* InPlayer);

private:
	ENUM_CLASS_FLAGS(ESpiderState, Wander, Chase, Search);
	enum class ESpiderState { Wander, Chase, Search };
	ESpiderState State = ESpiderState::Wander;

	ABugBreakPlayerCharacter* TargetPlayer = nullptr;
	float SearchTimer = 0.f;

	/**
	 * Moves toward a random navigation point.
	 * Input:  none
	 * Output: none
	 */
	void Wander();

	/**
	 * Moves toward the player's position.
	 * Input:  none
	 * Output: none
	 */
	void Chase();

	/**
	 * Counts down the search timer then returns to Wander.
	 * Input:  DeltaSeconds — frame time
	 * Output: none
	 */
	void Search(float DeltaSeconds);

	/**
	 * Returns true if the player is within detection radius and not hidden.
	 * Input:  none
	 * Output: bool
	 */
	bool CanSeePlayer() const;

	/**
	 * Returns true if the spider is within catch radius of the player.
	 * Input:  none
	 * Output: bool
	 */
	bool HasCaughtPlayer() const;

	/**
	 * Picks a random reachable point on the nav mesh and moves there.
	 * Input:  none
	 * Output: none
	 */
	void PickNewWanderTarget();
};
