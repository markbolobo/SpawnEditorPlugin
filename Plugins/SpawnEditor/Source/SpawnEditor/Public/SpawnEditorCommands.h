// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SpawnEditorStyle.h"

class FSpawnEditorCommands : public TCommands<FSpawnEditorCommands>
{
public:

	FSpawnEditorCommands()
		: TCommands<FSpawnEditorCommands>(TEXT("SpawnEditor"), NSLOCTEXT("Contexts", "SpawnEditor", "SpawnEditor Plugin"), NAME_None, FSpawnEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};