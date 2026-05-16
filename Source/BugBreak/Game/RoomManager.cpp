#include "RoomManager.h"
#include "Kismet/GameplayStatics.h"
#include "BugBreakGameMode.h"

void ARoomManager::InitializeRoom(int32 InRequiredBugCount)
{
	RequiredBugCount = InRequiredBugCount;
	FoundBugCount = 0;
}

void ARoomManager::RegisterFoundBug()
{
	FoundBugCount++;
	UE_LOG(LogTemp, Log, TEXT("Bugs found: %d / %d"), FoundBugCount, RequiredBugCount);

	if (IsRoomCleared())
	{
		ABugBreakGameMode* GM = Cast<ABugBreakGameMode>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			GM->AdvanceToNextRoom();
		}
	}
}

bool ARoomManager::IsRoomCleared() const
{
	return FoundBugCount >= RequiredBugCount;
}
