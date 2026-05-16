#include "SpiderAICharacter.h"
#include "../Player/BugBreakPlayerCharacter.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASpiderAICharacter::ASpiderAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpiderAICharacter::BeginPlay()
{
	Super::BeginPlay();
	TargetPlayer = Cast<ABugBreakPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PickNewWanderTarget();
}

void ASpiderAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	switch (State)
	{
	case ESpiderState::Wander: Wander(); break;
	case ESpiderState::Chase:  Chase();  break;
	case ESpiderState::Search: Search(DeltaSeconds); break;
	}
}

void ASpiderAICharacter::SetTargetPlayer(ABugBreakPlayerCharacter* InPlayer)
{
	TargetPlayer = InPlayer;
}

void ASpiderAICharacter::Wander()
{
	GetCharacterMovement()->MaxWalkSpeed = WanderSpeed;
	if (CanSeePlayer())
	{
		State = ESpiderState::Chase;
	}
}

void ASpiderAICharacter::Chase()
{
	if (!TargetPlayer) { State = ESpiderState::Wander; return; }

	if (TargetPlayer->IsHiddenState())
	{
		State = ESpiderState::Search;
		SearchTimer = SearchDuration;
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed = ChaseSpeed;

	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->MoveToActor(TargetPlayer, CatchRadius);
	}

	if (HasCaughtPlayer())
	{
		TargetPlayer->Die();
	}
}

void ASpiderAICharacter::Search(float DeltaSeconds)
{
	SearchTimer -= DeltaSeconds;
	if (SearchTimer <= 0.f)
	{
		State = ESpiderState::Wander;
		PickNewWanderTarget();
	}
}

bool ASpiderAICharacter::CanSeePlayer() const
{
	if (!TargetPlayer || TargetPlayer->IsHiddenState()) return false;
	return FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation()) < DetectionRadius;
}

bool ASpiderAICharacter::HasCaughtPlayer() const
{
	if (!TargetPlayer) return false;
	return FVector::Dist(GetActorLocation(), TargetPlayer->GetActorLocation()) < CatchRadius;
}

void ASpiderAICharacter::PickNewWanderTarget()
{
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys) return;

	FNavLocation NavLoc;
	if (NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 1200.f, NavLoc))
	{
		AAIController* AIC = Cast<AAIController>(GetController());
		if (AIC)
		{
			AIC->MoveToLocation(NavLoc.Location);
		}
	}
}
