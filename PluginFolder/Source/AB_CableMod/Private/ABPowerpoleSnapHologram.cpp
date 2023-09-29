#include "ABPowerpoleSnapHologram.h"
#include "AbstractInstanceManager.h"
#include "FGConstructDisqualifier.h"
#include "FGClearanceComponent.h"

bool AABPowerpoleSnapHologram::IsMatchingType(const FHitResult& hitResult) const {
	AActor* hitActor = hitResult.GetActor();

	if (AAbstractInstanceManager* hitAbstract = Cast<AAbstractInstanceManager>(hitActor)) {
		FInstanceHandle instHandle;
		hitAbstract->ResolveHit(hitResult, instHandle);
		hitActor = instHandle.GetOwner<AActor>();
	}

	if (hitActor == nullptr) { return false;  }

	for (int i = 0, l = mSnappableTo.Num(); i < l; i++) {
		UClass* testClass = mSnappableTo[i]->GetDefaultObject()->GetClass();
		if (hitActor->GetClass()->IsChildOf(testClass)) {
			return true;
		}
	}

	return false;
}

void AABPowerpoleSnapHologram::CheckValidFloor() {
	if (mSnappedBuilding != nullptr) { return; }

	Super::CheckValidFloor();
}

bool AABPowerpoleSnapHologram::TryUpgrade(const FHitResult& hitResult) {
	if (bExclusiveSnap) { return false; }

	return Super::TryUpgrade(hitResult);
}

bool AABPowerpoleSnapHologram::IsValidHitResult(const FHitResult& hitResult) const {
	if (bExclusiveSnap) {
		return IsMatchingType(hitResult);
	}

	return Super::IsValidHitResult(hitResult) || IsMatchingType(hitResult);
}

void AABPowerpoleSnapHologram::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	bool bValid = IsMatchingType(hitResult);
	mSnappedBuilding = nullptr;

	if (!bValid) {
		if (bExclusiveSnap) {
			SetActorLocation(hitResult.Location);
			AddConstructDisqualifier(UFGCDInvalidAimLocation::StaticClass());
			return;
		}
	} else {
		AFGBuildable* hitBuildable = Cast<AFGBuildable>(hitResult.GetActor());
		if (hitBuildable != nullptr && eSnapType != EABPoleSnapType::PST_None) {
			UFGClearanceComponent* clearanceSnap;
			FRotator rOffset;
			FVector lOffset;

			mSnappedBuilding = hitBuildable;

			switch (eSnapType) {
				case EABPoleSnapType::PST_HatSnap:
					clearanceSnap = hitBuildable->GetClearanceComponent();
					lOffset = clearanceSnap->GetRelativeLocation() + FVector(0.0f, 0.0f, clearanceSnap->GetScaledBoxExtent().Z);
					SetActorLocation(hitBuildable->GetTransform().TransformPosition(lOffset));
					SetActorRotation(hitBuildable->GetActorRotation());
					return;

				case EABPoleSnapType::PST_BackSnap:
					rOffset = FRotator(0.0f, 180.0f, 0.0f);
					SetActorLocation(hitBuildable->GetActorLocation());
					SetActorRotation(hitBuildable->GetActorRotation() + rOffset);
					return;
			}
		}
	}

	return Super::SetHologramLocationAndRotation(hitResult);
}
