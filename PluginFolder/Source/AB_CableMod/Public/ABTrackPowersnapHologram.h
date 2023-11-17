#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "ABTrackPowersnapHologram.generated.h"

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API AABTrackPowersnapHologram : public AFGBuildableHologram
{
	GENERATED_BODY()

	AABTrackPowersnapHologram();

public:
	virtual void ScrollRotate(int32 delta, int32 step) override;
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void ConfigureActor(class AFGBuildable* inBuildable) const;
	virtual void SetSnapToGuideLines(bool isEnabled);

public:
	bool bFlipped;
	bool bTrySpacing;
	AFGBuildableRailroadTrack* mSnappedTrack;
	FTransform lastTransform;
};
