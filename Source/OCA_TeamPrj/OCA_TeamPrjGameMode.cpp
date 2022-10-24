// Copyright Epic Games, Inc. All Rights Reserved.

#include "OCA_TeamPrjGameMode.h"
#include "OCA_TeamPrjCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOCA_TeamPrjGameMode::AOCA_TeamPrjGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
