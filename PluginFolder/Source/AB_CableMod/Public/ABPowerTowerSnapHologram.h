

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPowerPoleHologram.h"
#include "ABPowerTowerSnapHologram.generated.h"

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API AABPowerTowerSnapHologram : public AFGPowerPoleHologram
{
	GENERATED_BODY()

		//AABPowerTowerSnapHologram();

public:

	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "SnapLogic")
	TArray< TSubclassOf<AFGBuildable> > mSnappableTo;
};
