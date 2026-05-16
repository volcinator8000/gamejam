#include "BugBreakGameInstance.h"

void UBugBreakGameInstance::ResetRunState()
{
	bHasCoffee = false;
	CurrentRoomIndex = 0;
}

void UBugBreakGameInstance::SetHasCoffee(bool bInHasCoffee)
{
	bHasCoffee = bInHasCoffee;
}

void UBugBreakGameInstance::SetCurrentRoomIndex(int32 InRoomIndex)
{
	CurrentRoomIndex = InRoomIndex;
}
