// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpawnEditorCommands.h"

#define LOCTEXT_NAMESPACE "FSpawnEditorModule"

void FSpawnEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "SpawnEditor", "Bring up SpawnEditor window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
