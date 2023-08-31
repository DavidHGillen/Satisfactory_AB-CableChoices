// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#pragma once

#include "CoreMinimal.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Buildables/FGBuildableWire.h"
#include "Buildables/FGBuildableLightSource.h"
#include "FGCircuit.h"

#include "ABBuildablePowerline.generated.h"

USTRUCT()
struct AB_CABLEMOD_API FABPowerlineCustomization {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ABPowerline")
	UMaterialInterface* material;

	UPROPERTY(EditAnywhere, Category = "ABPowerline")
	UNiagaraSystem* particleFX;
};

/**
 * Adds several utility and setup functions for buildable cables
 * Note, tag is WireMesh
 */
UCLASS()
class AB_CABLEMOD_API AABBuildablePowerline : public AFGBuildableWire
{
	GENERATED_BODY()

public:
	AABBuildablePowerline();

protected:
	// Custom new properties ////
	// some skins and FX will need this to talk to lighting panels
	UPROPERTY(SaveGame/*, ReplicatedUsing = OnRep_LightControlData */)
	FLightSourceControlData mLightControlData;
	
	// many powerlines will need this so just manage it as a base property, beware perf tho
	UPROPERTY(SaveGame, EditInstanceOnly, Category = "ABPowerline")
	UNiagaraSystem* mParticleFX;

	// rather than modify the skin system, just let it do nothing and use this to do our thing TODO: ?unique per BP class only possible?
	UPROPERTY(EditDefaultsOnly, Category = "ABPowerline")
	TMap<TSubclassOf< UFGFactoryCustomizationDescriptor_Skin >, FABPowerlineCustomization> skinToData;



public:
	// AActor interface ////
	virtual void BeginPlay() override;

protected:
	// Factory interface ////
	//void ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData);
	void SetCustomizationData_Native(const FFactoryCustomizationData& customizationData);
};