#include "SwappableActor.h"
#include "../Game/RoomManager.h"
#include "Kismet/GameplayStatics.h"

ASwappableActor::ASwappableActor()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

void ASwappableActor::BeginPlay()
{
	Super::BeginPlay();
	if (bIsBugged && BuggedMesh)
	{
		MeshComp->SetStaticMesh(BuggedMesh);
	}
	else if (NormalMesh)
	{
		MeshComp->SetStaticMesh(NormalMesh);
	}
}

bool ASwappableActor::Interact(ABugBreakPlayerCharacter* InteractingPlayer)
{
	if (!bIsBugged || bWasFound) return false;

	bWasFound = true;

	ARoomManager* RM = Cast<ARoomManager>(UGameplayStatics::GetActorOfClass(this, ARoomManager::StaticClass()));
	if (RM)
	{
		RM->RegisterFoundBug();
	}

	return true;
}
