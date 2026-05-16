#include "BugBreakPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Game/BugBreakGameMode.h"

ABugBreakPlayerCharacter::ABugBreakPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ABugBreakPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABugBreakPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",   this, &ABugBreakPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABugBreakPlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Hide",     IE_Pressed, this, &ABugBreakPlayerCharacter::BeginHide);
}

void ABugBreakPlayerCharacter::MoveForward(float Value)
{
	if (bIsHidden || FMath::IsNearlyZero(Value)) return;
	const FVector Dir = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Dir, Value);
}

void ABugBreakPlayerCharacter::MoveRight(float Value)
{
	if (bIsHidden || FMath::IsNearlyZero(Value)) return;
	const FVector Dir = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Dir, Value);
}

void ABugBreakPlayerCharacter::Interact()
{
	if (!FocusedInteractable) return;
	// The Blueprint child or the interactable itself handles the actual logic.
	// We call an interface function here if you add an IInteractable interface later.
	UE_LOG(LogTemp, Log, TEXT("Interacting with: %s"), *FocusedInteractable->GetName());
}

void ABugBreakPlayerCharacter::BeginHide()
{
	if (bIsHidden)
	{
		EndHide();
		return;
	}
	if (!bCanHide) return;
	bIsHidden = true;
	GetCharacterMovement()->DisableMovement();
}

void ABugBreakPlayerCharacter::EndHide()
{
	bIsHidden = false;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void ABugBreakPlayerCharacter::SetCanHide(bool bInCanHide)
{
	bCanHide = bInCanHide;
	if (!bInCanHide && bIsHidden)
	{
		EndHide();
	}
}

void ABugBreakPlayerCharacter::Die()
{
	ABugBreakGameMode* GM = Cast<ABugBreakGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->HandlePlayerCaught();
	}
}
