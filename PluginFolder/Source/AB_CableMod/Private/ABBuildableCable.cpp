// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#include "ABBuildableCable.h"

// Satic init
//////////////////////////////////////////////////////


// Ctor
//////////////////////////////////////////////////////
AABBuildableCable::AABBuildableCable() {
}

// Factory interface
//////////////////////////////////////////////////////

// Custom
//////////////////////////////////////////////////////
void AABBuildableCable::MyUpdateWireMesh() {
	AFGBuildableWire* self = this;
	UE_LOG(LogTemp, Warning, TEXT("- CABLE MESH REBUILD - "));
}

