// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "AB_CableModModule.h"
#include "Buildables/FGBuildableWire.h"

#include "Patching/NativeHookManager.h"

void FAB_CableModModule::StartupModule() {


	// Hooking
	#if !WITH_EDITOR

	SUBSCRIBE_METHOD_AFTER(AFGBuildableWire::UpdateWireInstanceMesh, [](const FWireInstance& wireInstance) {
		UE_LOG(LogTemp, Warning, TEXT("--() UpdateWireInstanceMesh"));

		UStaticMeshComponent* meshRef = wireInstance.WireMesh;
		if (meshRef == NULL) { return; }

		// handle customization data updates for my classes
		AABBuildablePowerline::UpdateIfYours(&wireInstance);

		if(meshRef->GetCollisionProfileName() != FName("Hologram")) {
			// make everything respond to the customizer when it's not already a hologram
			meshRef->SetCollisionProfileName("BlockOnlyBuildGun", false);
		}
	});

	SUBSCRIBE_METHOD_AFTER(AFGBuildableWire::CreateWireInstance, [](FWireInstance wireInstance, const FVector& FirstLocation, const FVector& SecondLocation, const FTransform& WireTransform) {
		UE_LOG(LogTemp, Warning, TEXT("--() CreateWireInstance"));
	});

	SUBSCRIBE_METHOD_AFTER(AFGBuildableWire::CreateWireInstancesBetweenConnections, [](TArray< FWireInstance >& out_instances, class UFGCircuitConnectionComponent* first, class UFGCircuitConnectionComponent* second, const FTransform& WireTransform) {
		UE_LOG(LogTemp, Warning, TEXT("--() CreateWireInstancesBetweenConnections"));
	});

	SUBSCRIBE_METHOD_AFTER(AFGBuildableWire::UpdateWireMeshes, [](AFGBuildableWire* self) {
		UE_LOG(LogTemp, Warning, TEXT("--() UpdateWireMeshes"));
	});

	#endif
	// End Hooking
}

IMPLEMENT_GAME_MODULE(FAB_CableModModule, AB_CableMod);