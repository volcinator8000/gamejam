#include "MainMenuWidgetBase.h"
#include "../Game/BugBreakGameInstance.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenuWidgetBase::GetHasCoffee() const
{
	UBugBreakGameInstance* GI = Cast<UBugBreakGameInstance>(UGameplayStatics::GetGameInstance(this));
	return GI ? GI->GetHasCoffee() : false;
}

void UMainMenuWidgetBase::StartNewRun()
{
	UBugBreakGameInstance* GI = Cast<UBugBreakGameInstance>(UGameplayStatics::GetGameInstance(this));
	if (GI) GI->ResetRunState();
	UGameplayStatics::OpenLevel(this, FName("LV_Room00"));
}

void UMainMenuWidgetBase::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
