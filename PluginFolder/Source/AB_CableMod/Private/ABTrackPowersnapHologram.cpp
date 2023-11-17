#pragma once

#include "ABTrackPowersnapHologram.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGConstructDisqualifier.h"
#include "Math/UnrealMathUtility.h"
#include "ABBuildableRailPower.h"

AABTrackPowersnapHologram::AABTrackPowersnapHologram() {
	bFlipped = false;
	bTrySpacing = false;
	mSnappedTrack = nullptr;

	mGridSnapSize = 100.0f;
	mNeedsValidFloor = false;
	mCanLockHologram = false;
	mCanNudgeHologram = false;
	mSnapToGuideLines = false;
	mCanSnapWithAttachmentPoints = false;
	mCanBePlacedInBlueprintDesigner = false;
}

void AABTrackPowersnapHologram::ScrollRotate(int32 delta, int32 step) {
	bFlipped = !bFlipped;
}

bool AABTrackPowersnapHologram::IsValidHitResult(const FHitResult& hitResult) const {
	return Cast<AFGBuildableRailroadTrack>(hitResult.GetActor()) != nullptr;
}

bool AABTrackPowersnapHologram::TrySnapToActor(const FHitResult& hitResult) {
	AFGBuildableRailroadTrack* testTrack = Cast<AFGBuildableRailroadTrack>(hitResult.GetActor());
	if (testTrack == nullptr) { // occurs when holding down T to snap to guidelines and moving aim off the rail
		AddConstructDisqualifier(UFGCDMustHaveRailRoadTrack::StaticClass());
		return false;
	}

	bool bChangedTrack = testTrack != mSnappedTrack && mSnappedTrack != nullptr; // no track to some track isn't a change
	USplineComponent* splineRef = testTrack->GetSplineComponent();
	mSnappedTrack = testTrack;

	if (bTrySpacing) {
		// tracks may not have an even length so figure out closest spacing that will snap to both ends nicely
		float length = splineRef->GetSplineLength();
		int32 count = FMath::RoundToInt(length / mGridSnapSize);
		float spacingSize = length / count;

		// snap the impact point into our calculated spacings
		float distance = splineRef->FindDistanceClosestToWorldLocation(hitResult.Location);
		count = FMath::RoundToInt(distance / spacingSize);
		distance = spacingSize * count;

		SetActorTransform(splineRef->GetTransformAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World, true));
	} else {
		SetActorTransform(splineRef->FindTransformClosestToWorldLocation(hitResult.Location, ESplineCoordinateSpace::World, true));
	}
	if (bFlipped) {
		AddActorLocalRotation(FRotator(0.0, 180.0, 0.0));
	}

	FTransform currentTransform = GetTransform();
	FVector const sideways = FVector(0.0, 1.0, 0.0);

	// negative DOT means they're facing >90d away from each other, so flipping the box will make final world rotation closer
	if (bChangedTrack && lastTransform.TransformVector(sideways).Dot(currentTransform.TransformVector(sideways)) < 0.0) {
		bFlipped = !bFlipped;
		AddActorLocalRotation(FRotator(0.0, 180.0, 0.0));
	}

	lastTransform = currentTransform;

	return true;
}

void AABTrackPowersnapHologram::ConfigureActor(class AFGBuildable* inBuildable) const {
	Super::ConfigureActor(inBuildable);

	AABBuildableRailPower* PowerBox = Cast<AABBuildableRailPower>(inBuildable);
	if(PowerBox != nullptr) {
		PowerBox->mSnappedTrack = mSnappedTrack;
	}
}

void AABTrackPowersnapHologram::SetSnapToGuideLines(bool isEnabled) {
	bTrySpacing = isEnabled;
}
