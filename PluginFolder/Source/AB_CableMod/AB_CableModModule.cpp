// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "AB_CableModModule.h"

#include "Patching/NativeHookManager.h"

void FAB_CableModModule::StartupModule() {


	// Hooking
	//////////////////////////////////////////////////////
	#if !WITH_EDITOR
//	SUBSCRIBE_METHOD(AFGHoverPack::ConnectToPowerConnection, [](auto& scope, AFGHoverPack* self, class UFGPowerConnectionComponent* Connection) {
//		UE_LOG(HoverPackPoleRange_Log, Display, TEXT("Starting Hook"));
//
//		UE_LOG(HoverPackPoleRange_Log, Display, TEXT("end"));
//
//	});
	#endif
}

IMPLEMENT_GAME_MODULE(FAB_CableModModule, AB_CableMod);