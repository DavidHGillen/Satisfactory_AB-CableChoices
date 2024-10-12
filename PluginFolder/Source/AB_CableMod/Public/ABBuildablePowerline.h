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
	// Custom new properties
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
	// AActor interface
	virtual void OnConstruction(const FTransform& transform) override;
	virtual void BeginPlay() override;

protected:

	//~ Begin IFGColorInterface
	void SetCustomizationData_Implementation(const FFactoryCustomizationData& customizationData);
	void SetCustomizationData_Native(const FFactoryCustomizationData& customizationData, bool skipCombine = false);
	void ApplyCustomizationData_Implementation(const FFactoryCustomizationData& customizationData);
	void ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData);
	FFactoryCustomizationData GetCustomizationData_Implementation();
	FFactoryCustomizationData& GetCustomizationData_Native();
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Implementation();
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Native();
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Native();
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Implementation();
	//bool GetCanBeColored_Implementation();
	//bool GetCanBePatterned_Implementation();
	virtual bool IsColorApplicationDeferred();
	virtual bool CanApplyDeferredColorToBuildable(FVector hitLocation, FVector hitNormal, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController);
	virtual void ApplyDeferredColorToBuildable(FVector hitLocation, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController);
	virtual void StartIsAimedAtForColor_Implementation(class AFGCharacterPlayer* byCharacter, bool isValid = true);
	virtual void StopIsAimedAtForColor_Implementation(class AFGCharacterPlayer* byCharacter);
	//~ End IFGColorInterface
	
	/* Build/Dismantle Effects */
	virtual void PlayBuildEffects(AActor* inInstigator);
	virtual void ExecutePlayBuildEffects();
	virtual void OnBuildEffectFinished();

	void OnMaterialInstancesUpdated();
	void OnSkinCustomizationApplied(TSubclassOf< class UFGFactoryCustomizationDescriptor_Skin > skin);

	void ApplySkinData(TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > newSkinDesc);
	void ApplyMeshPrimitiveData(const FFactoryCustomizationData& customizationData);

	void OnRep_CustomizationData();

	virtual void Native_OnMaterialInstancesUpdated();
};