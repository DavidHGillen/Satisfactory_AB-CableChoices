#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPowerPoleHologram.h"
#include "ABPowerpoleSnapHologram.generated.h"

UENUM()
enum class EABPoleSnapType : uint8
{
	PST_None,
	PST_HatSnap, // top of the clearance box
	PST_BackSnap // spun 180 to be back to back
};

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API AABPowerpoleSnapHologram : public AFGPowerPoleHologram
{
	GENERATED_BODY()

public:

	bool IsMatchingType(const FHitResult& hitResult) const;

	virtual void CheckValidFloor() override;
	virtual bool TryUpgrade(const FHitResult& hitResult) override;
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "SnapLogic")
	bool bExclusiveSnap = false;

	UPROPERTY(EditDefaultsOnly, Category = "SnapLogic")
	EABPoleSnapType eSnapType;

	UPROPERTY(EditDefaultsOnly, Category = "SnapLogic")
	TArray< TSubclassOf<AFGBuildable> > mSnappableTo;
};
