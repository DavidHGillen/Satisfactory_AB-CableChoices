#include "ABPowerTowerSnapHologram.h"
#include "FGConstructDisqualifier.h"

bool AABPowerTowerSnapHologram::IsValidHitResult(const FHitResult& hitResult) const { return true;  }

void AABPowerTowerSnapHologram::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	//return Super::SetHologramLocationAndRotation(hitResult);

	bool bValid = false;
	AFGBuildable* hitActor = Cast<AFGBuildable>(hitResult.GetActor());

	for (int i = 0, l = mSnappableTo.Num(); i < l; i++) {
		if (hitActor->StaticClass()->IsChildOf(mSnappableTo[i].Get()->StaticClass())) { bValid = true; break; }
	}

	if(bValid) {
		UFGClearanceComponent* clearanceSnap = hitActor->GetClearanceComponent();
		SetActorLocation(hitActor->GetActorLocation());
		SetActorRotation(hitActor->GetActorRotation());
	} else {
		SetActorLocation(hitResult.Location);
		AddConstructDisqualifier(UFGCDInvalidAimLocation::StaticClass());
	}
}
