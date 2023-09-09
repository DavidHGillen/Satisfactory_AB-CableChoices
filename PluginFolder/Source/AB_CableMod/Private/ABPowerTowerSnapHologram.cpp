#include "ABPowerTowerSnapHologram.h"
#include "AbstractInstanceManager.h"
#include "FGConstructDisqualifier.h"
#include "FGClearanceComponent.h"

bool AABPowerTowerSnapHologram::IsValidHitResult(const FHitResult& hitResult) const {
	AActor* hitActor = hitResult.GetActor();
	if (AAbstractInstanceManager* hitAbstract = Cast<AAbstractInstanceManager>(hitActor)) {
		FInstanceHandle instHandle;
		hitAbstract->ResolveHit(hitResult, instHandle);
		hitActor = instHandle.GetOwner<AActor>();
	}

	AFGBuildable* hitBuildable = Cast<AFGBuildable>(hitActor);
	if (hitBuildable == NULL) { return false; }

	for (int i = 0, l = mSnappableTo.Num(); i < l; i++) {
		if (hitActor->GetClass()->IsChildOf(mSnappableTo[i]->GetDefaultObject()->GetClass())) { return true; }
	}

	return false;
}

void AABPowerTowerSnapHologram::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	AActor* hitActor = hitResult.GetActor();
	if (AAbstractInstanceManager* hitAbstract = Cast<AAbstractInstanceManager>(hitActor)) {
		FInstanceHandle instHandle;
		hitAbstract->ResolveHit(hitResult, instHandle);
		hitActor = instHandle.GetOwner<AActor>();
	}

	AFGBuildable* hitBuildable = Cast<AFGBuildable>(hitActor);
	if (hitBuildable == NULL) { return; }

	bool bValid = false;
	for (int i = 0, l = mSnappableTo.Num(); i < l; i++) {
		if (hitActor->GetClass()->IsChildOf(mSnappableTo[i]->GetDefaultObject()->GetClass())) { bValid = true; break; }
	}

	if(bValid) {
		UFGClearanceComponent* clearanceSnap = hitBuildable->GetClearanceComponent();
		FVector offset = FVector(0.0f, 0.0f, clearanceSnap->GetScaledBoxExtent().Z);
		SetActorLocation(clearanceSnap->GetComponentLocation() + offset);
		SetActorRotation(hitBuildable->GetActorRotation());
	} else {
		SetActorLocation(hitResult.Location);
		AddConstructDisqualifier(UFGCDInvalidAimLocation::StaticClass());
	}
}
