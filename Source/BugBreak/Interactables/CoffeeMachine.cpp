#include "CoffeeMachine.h"
#include "../Player/BugBreakPlayerCharacter.h"
#include "../Game/BugBreakGameMode.h"
#include "Kismet/GameplayStatics.h"

ACoffeeMachine::ACoffeeMachine()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool ACoffeeMachine::Interact(ABugBreakPlayerCharacter* InteractingPlayer)
{
	if (!InteractingPlayer) return false;

	ABugBreakGameMode* GM = Cast<ABugBreakGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->HandleCoffeeReached();
		return true;
	}
	return false;
}
