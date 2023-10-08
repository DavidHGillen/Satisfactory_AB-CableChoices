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
	if (testTrack == nullptr) { // occurs when holding down T to snap to guidelines and moving off the rail
		AddConstructDisqualifier(UFGCDInvalidAimLocation::StaticClass());
		return false;
	}

	bool bNewTrack = testTrack != mSnappedTrack;
	USplineComponent* splineRef = testTrack->GetSplineComponent();
	FTransform oldTransform = GetTransform();
	mSnappedTrack = testTrack;

	if (bTrySpacing) {
		float length = splineRef->GetSplineLength();
		int32 count = FMath::RoundToInt(length / mGridSnapSize);
		float spacingSize = length / count;

		float distance = splineRef->FindDistanceClosestToWorldLocation(hitResult.Location);
		count = FMath::RoundToInt(distance / spacingSize);
		distance = spacingSize * count;

		SetActorTransform(splineRef->GetTransformAtDistanceAlongSpline(distance, ESplineCoordinateSpace::World, true));
	} else {
		SetActorTransform(splineRef->FindTransformClosestToWorldLocation(hitResult.Location, ESplineCoordinateSpace::World, true));
	}

	if (bNewTrack) {
		bFlipped = oldTransform.GetUnitAxis(EAxis::Y).Dot(GetTransform().GetUnitAxis(EAxis::Y)) < 0;
	}
	if (bFlipped) {
		AddActorLocalRotation(FRotator(0, 180, 0));
	}

	return true;
}

void AABTrackPowersnapHologram::ConfigureActor(class AFGBuildable* inBuildable) const {
	AABBuildableRailPower* PowerBox = Cast<AABBuildableRailPower>(inBuildable);
	if(PowerBox != nullptr) {
		PowerBox->mSnappedTrack = mSnappedTrack;
	}
}

void AABTrackPowersnapHologram::SetSnapToGuideLines(bool isEnabled) {
	bTrySpacing = isEnabled;
}
