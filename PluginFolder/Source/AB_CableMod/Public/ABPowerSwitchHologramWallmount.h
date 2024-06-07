// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPowerSwitchHologram.h"
#include "Buildables/FGBuildableFactory.h"
#include "ABPowerSwitchHologramWallmount.generated.h"

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API AABPowerSwitchHologramWallmount : public AFGPowerSwitchHologram
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hologram|Wallmount")
	bool snapToWalls = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hologram|Wallmount")
	bool snapToFoundationSides = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hologram|Wallmount")
	bool allowSpinOnWall = true;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hologram|Wallmount")
	//TMap<TSubclassOf<AFGBuildableFactory>, TPair<EAxis::Type, float>> poleSnapRules;

// Factory Game
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
};
