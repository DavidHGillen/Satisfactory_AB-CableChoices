// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "AB_CableModModule.h"
#include "Buildables/FGBuildableWire.h"

#include "Patching/NativeHookManager.h"

void FAB_CableModModule::StartupModule() {


	// Hooking
	#if !WITH_EDITOR

	SUBSCRIBE_METHOD_AFTER(AFGBuildableWire::UpdateWireInstanceMesh, [](void, const FWireInstance& wireInstance) {
		//UE_LOG(LogTemp, Warning, TEXT("--() UpdateWireInstanceMesh"));
		// 
		// handle customization data updates for my classes
		AABBuildablePowerline::UpdateIfYours(&wireInstance);
		// make everything respond to the customizer
		wireInstance.WireMesh->SetCollisionProfileName("BlockOnlyBuildGun", false);
		wireInstance.WireMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	});// */

	#endif
	// End Hooking
}

IMPLEMENT_GAME_MODULE(FAB_CableModModule, AB_CableMod);