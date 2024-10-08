#include "ABPowerpoleSnapHologram.h"

#include "AbstractInstanceManager.h"
#include "FGConstructDisqualifier.h"

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

void AABPowerpoleSnapHologram::ScrollRotate(int32 delta, int32 step) {
	if (eSnapType == EABPoleSnapType::PST_HatSnapSpin && mSnappedBuilding != nullptr) {
		bRotate90 = !bRotate90;
	} else {
		Super::ScrollRotate(delta, step);
	}
}

bool AABPowerpoleSnapHologram::TryUpgrade(const FHitResult& hitResult) {
	if (bExclusiveSnap) { return false; }

	bool didUpgrade = Super::TryUpgrade(hitResult);

	if (didUpgrade && bSpinOnReplace){
		AddActorLocalRotation(FRotator(0.0f, GetScrollRotateValue(), 0.0f));
	}

	return didUpgrade;
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
			FRotator rotOffset;
			FVector locOffset;

			mSnappedBuilding = hitBuildable;

			if (eSnapType == EABPoleSnapType::PST_BackSnap) {
				rotOffset = FRotator(0.0f, 180.0f, 0.0f);
				SetActorLocation(hitBuildable->GetActorLocation());
				SetActorRotation(hitBuildable->GetActorRotation() + rotOffset);
				return;
			} else if (eSnapType == EABPoleSnapType::PST_HatSnap || eSnapType == EABPoleSnapType::PST_HatSnapSpin) {
				FBox clearanceSnap = mSnappedBuilding->GetCombinedClearanceBox();
				locOffset = FVector(0.0f, 0.0f, clearanceSnap.Max.Z);
				SetActorLocation(hitBuildable->GetTransform().TransformPosition(locOffset));
				SetActorRotation(hitBuildable->GetActorRotation());
				if (eSnapType == EABPoleSnapType::PST_HatSnapSpin && bRotate90) {
					AddActorLocalRotation(FRotator(0.0f, 90.0f, 0.0f));
				}
				return;
			}
		}
	}

	Super::SetHologramLocationAndRotation(hitResult);
	return;
}
