// Copyright David "Angry Beaver" Gillen, details listed on associated mods Readme

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableWire.h"
#include "FGCircuit.h"

#include "ABBuildablePowerline.generated.h"

/**
 * Adds several utility and setup functions for buildable cables
 * Note, tag is WireMesh
 */
UCLASS()
class AB_CABLEMOD_API AABBuildablePowerline : public AFGBuildableWire
{
	GENERATED_BODY()

	AABBuildablePowerline();

public:

protected:
	// Factory interface
	//////////////////////////////////////////////////////

	void SetCustomizationData_Implementation(const FFactoryCustomizationData& customizationData);
	void SetCustomizationData_Native(const FFactoryCustomizationData& customizationData);

	void ApplySkinData(TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > newSkinDesc);

	/*void SetCustomizationData_Implementation(const FFactoryCustomizationData& customizationData);
	void SetCustomizationData_Native(const FFactoryCustomizationData& customizationData);
	void ApplyCustomizationData_Implementation(const FFactoryCustomizationData& customizationData);
	void ApplyCustomizationData_Native(const FFactoryCustomizationData& customizationData);
	FFactoryCustomizationData GetCustomizationData_Implementation() { return mCustomizationData; }
	FFactoryCustomizationData& GetCustomizationData_Native() { return mCustomizationData; }
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Implementation() { return mFactorySkinClass; }
	TSubclassOf< UFGFactorySkinActorData > GetFactorySkinClass_Native() { return mFactorySkinClass; }
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Native();
	TSubclassOf< UFGFactoryCustomizationDescriptor_Skin > GetActiveSkin_Implementation();
	bool GetCanBeColored_Implementation();
	bool GetCanBePatterned_Implementation();
	virtual bool IsColorApplicationDeferred() { return false; }
	virtual bool CanApplyDeferredColorToBuildable(FVector hitLocation, FVector hitNormal, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController) { return false; }
	virtual void ApplyDeferredColorToBuildable(FVector hitLocation, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > swatch, APlayerController* playerController) {};
	virtual void StartIsAimedAtForColor_Implementation(class AFGCharacterPlayer* byCharacter, bool isValid = true);
	virtual void StopIsAimedAtForColor_Implementation(class AFGCharacterPlayer* byCharacter);

	UFUNCTION(BlueprintImplementableEvent, Category = "Buildable|Build Effect")
		void OnMaterialInstancesUpdated();

	UFUNCTION(BlueprintNativeEvent, Category = "Buildable|Customization")
		void OnSkinCustomizationApplied(TSubclassOf< class UFGFactoryCustomizationDescriptor_Skin > skin);

	UFUNCTION(BlueprintCallable, Category = "Buildable|Customization")
		void ApplyMeshPrimitiveData(const FFactoryCustomizationData& customizationData);

	FORCEINLINE virtual float GetEmissivePower() { return 1.f; }

	UPROPERTY(SaveGame, ReplicatedUsing = OnRep_CustomizationData, meta = (NoAutoJson = true))
		FFactoryCustomizationData mCustomizationData;
	
	/**/

	/*
		TSubclassOf< UFGFactoryCustomizationDescriptor_Swatch > mDefaultSwatchCustomizationOverride;
		TSubclassOf< class UFGSwatchGroup > mSwatchGroup;
		TSubclassOf< class UFGFactorySkinActorData > mFactorySkinClass;
	/**/
};