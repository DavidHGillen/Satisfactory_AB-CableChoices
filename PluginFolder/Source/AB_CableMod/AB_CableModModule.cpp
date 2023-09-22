// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "AB_CableModModule.h"
#include "Buildables/FGBuildableLightsControlPanel.h"

#include "Patching/NativeHookManager.h"

void FAB_CableModModule::StartupModule() {


	// Hooking
	//////////////////////////////////////////////////////
	//*
	#if !WITH_EDITOR

	SUBSCRIBE_METHOD(AFGBuildableLightsControlPanel::SetLightControlData, [](auto& scope, AFGBuildableLightsControlPanel* self, FLightSourceControlData data) {
		UE_LOG(LogTemp, Warning, TEXT("PANEL [[[ SetLightControlData ]]] PANEL"));
	});

	#endif
	//*/
}

IMPLEMENT_GAME_MODULE(FAB_CableModModule, AB_CableMod);