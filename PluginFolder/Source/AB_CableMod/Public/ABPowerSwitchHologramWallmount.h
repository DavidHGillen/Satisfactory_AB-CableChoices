// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPowerSwitchHologram.h"
#include "Buildables/FGBuildableFactory.h"
#include "ABPowerSwitchHologramWallmount.generated.h"

/**
 * Collection of info used for succesfull snapping layout to power/light poles
 */
USTRUCT(BlueprintType)
struct FPoleSnapData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TSubclassOf<AFGBuildable> buildableClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float minDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float maxDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	FVector offset;
};

// Actual hologram class //

/**
 * Powerswitch hologram class extension.
 * For powerswitches that should be able to attach to walls, poles, and other situations
 */
UCLASS()
class AB_CABLEMOD_API AABPowerSwitchHologramWallmount : public AFGPowerSwitchHologram {
	GENERATED_BODY()

	AABPowerSwitchHologramWallmount();

public:
	// enable spinning against the attached surface
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hologram|Wallmount")
	bool allowSpinOnWall = true;

	// how far to position from a wall specifically
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hologram|Wallmount")
	float wallOffset = 25.0f;

	// if limiting rotation to major rotations steps, how precise
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hologram|Wallmount")
	uint8 majorRotation = 2;

	// first come first served ordered array of rules for pole snapping
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hologram|Wallmount")
	TArray<FPoleSnapData> poleSnapRules;

	virtual float GetRotationMajorFinal();
	virtual void BeginPlay() { Super::BeginPlay();  this->mScrollRotation = 0.0f; }; //attempt to fix intermittent random 5d rot

// Factory Game
	virtual int32 GetRotationStep() const { return 15; };
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool CanNudgeHologram() const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
};
