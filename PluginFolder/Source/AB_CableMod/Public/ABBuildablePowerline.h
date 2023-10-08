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
	//UPROPERTY(SaveGame/*, ReplicatedUsing = OnRep_LightControlData */)
	//FLightSourceControlData mLightControlData;
	
	// many powerlines will need this so just manage it as a base property, beware perf tho
	UPROPERTY(SaveGame, EditInstanceOnly, Category = "ABPowerline")
	UNiagaraSystem* mParticleFX;

	// rather than modify the skin system, just let it do nothing and use this to do our thing
	UPROPERTY(EditDefaultsOnly, Category = "ABPowerline")
	TMap<TSubclassOf< UFGFactoryCustomizationDescriptor_Skin >, FABPowerlineCustomization> skinToData;

	// trying to include a default in the map was just not working reliably
	UPROPERTY(EditDefaultsOnly, Category = "ABPowerline")
	FABPowerlineCustomization defaultData;

public:
	// AActor interface ////
	virtual void BeginPlay() override;

protected:
	// Factory interface ////
	void ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData);

	/*
	virtual void OnBuildEffectFinished() override;

	virtual void Native_OnMaterialInstancesUpdated() override;
	virtual void PostLazySpawnInstances_Implementation() override;

	void ApplyCustomizationData_Implementation(const FFactoryCustomizationData& customizationData);

	void SetCustomizationData_Implementation(const FFactoryCustomizationData& customizationData);
	void SetCustomizationData_Native(const FFactoryCustomizationData& customizationData);

	FFactoryCustomizationData GetCustomizationData_Implementation() { return mCustomizationData; }
	FFactoryCustomizationData& GetCustomizationData_Native() { return mCustomizationData; }
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Implementation() { return mFactorySkinClass; }
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Native() { return mFactorySkinClass; }
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Native();
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Implementation();

	virtual bool IsColorApplicationDeferred() override;
	virtual bool CanApplyDeferredColorToBuildable(FVector hitLocation, FVector hitNormal, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController) override;
	virtual void ApplyDeferredColorToBuildable(FVector hitLocation, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController) override;
	virtual void StartIsAimedAtForColor_Implementation(class AFGCharacterPlayer* byCharacter, bool isValid = true) override;
	virtual void StopIsAimedAtForColor_Implementation(class AFGCharacterPlayer* byCharacter) override;

	bool GetCanBeColored_Implementation();
	bool GetCanBePatterned_Implementation();

	void OnMaterialInstancesUpdated();
	void OnSkinCustomizationApplied(TSubclassOf< class UFGFactoryCustomizationDescriptor_Skin > skin);

	void ApplySkinData(TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > newSkinDesc);
	void ApplyMeshPrimitiveData(const FFactoryCustomizationData& customizationData);

	void OnRep_CustomizationData();
	//*/
};