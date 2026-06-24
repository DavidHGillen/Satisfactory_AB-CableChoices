// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPowerPoleHologram.h"
#include "ABPowerPoleCornerHologram.generated.h"

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API AABPowerPoleCornerHologram : public AFGPowerPoleHologram
{
	GENERATED_BODY()

protected:
	/** -1,0,1 to indicate whether we're at that extent or in the middle **/
	int xExtent = 0;
	int yExtent = 0;
	int zExtent = 0;

	bool bNarrowFlip = false; // If we're on a wall or other narrow surface rotating should flip between sides

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TSubclassOf<AFGBuildable> buildableClass;

	// Factory Game
	virtual void CheckValidPlacement() override {}; // necessary to stop yelling about floors and such
	virtual int32 GetRotationStep() const { return 0; }; // we only ever flip a rotation just confuses the issue

	virtual void ScrollRotate(int32 delta, int32 step) override;
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;

	//virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;

	// custom
	virtual void RotateToMatchExtents(FQuat& outRotation);
	virtual void ApplyXExtent(float border, float hitPos, float min, float max, FVector& outLocation);
	virtual void ApplyYExtent(float border, float hitPos, float min, float max, FVector& outLocation);
	virtual void ApplyZExtent(float border, float hitPos, float min, float max, FVector& outLocation);
};
