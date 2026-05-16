#include "BugBreakGameMode.h"
#include "BugBreakGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ABugBreakGameMode::AdvanceToNextRoom()
{
	UBugBreakGameInstance* GI = Cast<UBugBreakGameInstance>(GetGameInstance());
	if (!GI) return;

	int32 Next = GI->GetCurrentRoomIndex() + 1;
	GI->SetCurrentRoomIndex(Next);

	if (Next >= TotalRooms)
	{
		UGameplayStatics::OpenLevel(this, FName(*CoffeeRoomMap));
	}
	else
	{
		LoadRoomByIndex(Next);
	}
}

void ABugBreakGameMode::HandlePlayerCaught()
{
	LoadMainMenu(false);
}

void ABugBreakGameMode::HandleCoffeeReached()
{
	LoadMainMenu(true);
}

void ABugBreakGameMode::LoadMainMenu(bool bWithCoffee)
{
	UBugBreakGameInstance* GI = Cast<UBugBreakGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->SetHasCoffee(bWithCoffee);
	}
	UGameplayStatics::OpenLevel(this, FName(*MainMenuMap));
}

void ABugBreakGameMode::LoadRoomByIndex(int32 RoomIndex)
{
	FString MapName = FString::Printf(TEXT("%s%02d"), *RoomMapPrefix, RoomIndex);
	UGameplayStatics::OpenLevel(this, FName(*MapName));
}
