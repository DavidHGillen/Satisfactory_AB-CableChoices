// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPowerPoleWallHologram.h"
#include "ABPowerPoleCornerHologram.generated.h"

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API AABPowerPoleCornerHologram : public AFGPowerPoleWallHologram
{
	GENERATED_BODY()

protected:
	/** -1,0,1 to indicate whether we're at that extent or in the middle **/
	int xExtent = 0;
	int yExtent = 0;
	int zExtent = 0;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TSubclassOf<AFGBuildable> buildableClass;

	// Factory Game
	virtual void CheckValidPlacement() override {}; // necessary to stop yelling about walls and such
	virtual int32 GetRotationStep() const { return 0; };
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	//virtual bool CanNudgeHologram() const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	//virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;

	// custom
	virtual void RotateToMatchExtents(FQuat& outRotation);
};
