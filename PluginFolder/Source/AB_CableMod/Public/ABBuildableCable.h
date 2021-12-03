// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableWire.h"
#include "FGCircuit.h"

#include "ABBuildableCable.generated.h"

/**
 * Adds several utility and setup functions for buildable cables
 */
UCLASS()
class AB_CABLEMOD_API AABBuildableCable : public AFGBuildableWire
{
	GENERATED_BODY()

	AABBuildableCable();

public:

protected:
	// Factory interface
	//////////////////////////////////////////////////////

	// Custom
	//////////////////////////////////////////////////////
	void MyUpdateWireMesh();
};