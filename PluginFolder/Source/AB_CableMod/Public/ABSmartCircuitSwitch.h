#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableCircuitSwitch.h"

#include "ABSmartCircuitSwitch.generated.h"

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API AABSmartCircuitSwitch : public AFGBuildableCircuitSwitch
{
	GENERATED_BODY()

public:
	AABSmartCircuitSwitch();
	
public:
	// custom

	/* What does the logic of the switch want the physical switch to be doing, more than just the switch state
	* -1 is disconnected
	* 0 is off and stable
	* 1 is on and stable
	* 2 is transitioning
	* higher is a special case, may rework as a bit field & enums at some point, unclear
	*/
	UPROPERTY(SaveGame, BlueprintReadWrite, EditInstanceOnly, Replicated)
	int iCustomState = -1;

protected:
	// custom

	//How long from the key moment till the occurance, may be ignored by some switches
	UPROPERTY(SaveGame, EditAnywhere, Replicated, Category = "SmartSwitch")
	float fWaitLength = 5.0f;

	// GameTime in Seconds moment the trigger should occur
	UPROPERTY(EditInstanceOnly, Replicated)
	float fGameTime_Trigger;

	// 0-1 percentage of time left when the save occured, used for loading
	UPROPERTY(SaveGame)
	float fProgressAtSave = 0.0f;

public:
	// base classes
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// custom

	//
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "SmartSwitch")
	void BPUpdateVisualData();

	//
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SmartSwitch")
	float GetWaitTime() { return fWaitLength; }

	//
	UFUNCTION(BlueprintCallable, Category = "SmartSwitch")
	void SetWaitTime(float newTime) { fWaitLength = FMath::Max(0.0001f, fWaitLength); }

	//
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SmartSwitch")
	float GetTriggerMoment() { return fGameTime_Trigger; };

	//
	UFUNCTION(BlueprintCallable, Category = "SmartSwitch")
	void ResetTriggerMoment(bool bResetProgress, float fNewWaitLength = -1.0f);

	//
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SmartSwitch")
	float GetClampedProgressAtTime(float fGameTime = -1.0f);

protected:
	// base classes
	void ApplyMeshPrimitiveData(const FFactoryCustomizationData& customizationData) {
		Super::ApplyMeshPrimitiveData(customizationData);
		BPUpdateVisualData();
	};

	virtual void PreSave(FObjectPreSaveContext SaveContext);
	virtual void PostLoad();
};
