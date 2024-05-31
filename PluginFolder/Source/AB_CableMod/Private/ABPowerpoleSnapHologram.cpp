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

void AABPowerpoleSnapHologram::ScrollRotate(int32 delta, int32 step) {
	if (eSnapType == EABPoleSnapType::PST_HatSnapSpin && mSnappedBuilding != nullptr) {
		bRotate90 = !bRotate90;
	} else {
		Super::ScrollRotate(delta, step);
	}
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

			if (eSnapType == EABPoleSnapType::PST_BackSnap) {
				rOffset = FRotator(0.0f, 180.0f, 0.0f);
				SetActorLocation(hitBuildable->GetActorLocation());
				SetActorRotation(hitBuildable->GetActorRotation() + rOffset);
				return;
			} else if (eSnapType == EABPoleSnapType::PST_HatSnap || eSnapType == EABPoleSnapType::PST_HatSnapSpin) {
				clearanceSnap = hitBuildable->GetClearanceComponent();
				lOffset = clearanceSnap->GetRelativeLocation() + FVector(0.0f, 0.0f, clearanceSnap->GetScaledBoxExtent().Z);
				SetActorLocation(hitBuildable->GetTransform().TransformPosition(lOffset));
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
