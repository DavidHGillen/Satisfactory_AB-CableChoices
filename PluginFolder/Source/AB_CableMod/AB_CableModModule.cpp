// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "AB_CableModModule.h"
#include "Buildables/FGBuildableLightsControlPanel.h"
#include "Buildables/FGBuildableWire.h"
#include "Buildables/FGBuildable.h"

#include "Patching/NativeHookManager.h"

void FAB_CableModModule::StartupModule() {


	// Hooking
	//////////////////////////////////////////////////////
	#if !WITH_EDITOR

	/*SUBSCRIBE_METHOD(AFGBuildable::_____________, [](auto& scope, AFGBuildable* self, aaaaaaaaaaaaaaaaaaaaa) {
		UE_LOG(LogTemp, Warning, TEXT("[[[ [[[ [[[ _____________"));
	});*/

	#endif
	//
}

IMPLEMENT_GAME_MODULE(FAB_CableModModule, AB_CableMod);