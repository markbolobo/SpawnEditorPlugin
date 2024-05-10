// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpawnEditor.h"
#include "SpawnEditorStyle.h"
#include "SpawnEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName SpawnEditorTabName("SpawnEditor");

#define LOCTEXT_NAMESPACE "FSpawnEditorModule"

void FSpawnEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSpawnEditorStyle::Initialize();
	FSpawnEditorStyle::ReloadTextures();

	FSpawnEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSpawnEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSpawnEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSpawnEditorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SpawnEditorTabName, FOnSpawnTab::CreateRaw(this, &FSpawnEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FSpawnEditorTabTitle", "SpawnEditor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FSpawnEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSpawnEditorStyle::Shutdown();

	FSpawnEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SpawnEditorTabName);
}

TSharedRef<SDockTab> FSpawnEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FSpawnEditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("SpawnEditor.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FSpawnEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(SpawnEditorTabName);
}

void FSpawnEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FSpawnEditorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSpawnEditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSpawnEditorModule, SpawnEditor)