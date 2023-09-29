#pragma once

#include "ABTrackPowersnapHologram.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "ABBuildableRailPower.h"

AABTrackPowersnapHologram::AABTrackPowersnapHologram() {
	bFlipped = false;
	mSnappedTrack = nullptr;
}

void AABTrackPowersnapHologram::CheckValidFloor() {} // any floor is valid so long as we're snapped to a railway

void AABTrackPowersnapHologram::ScrollRotate(int32 delta, int32 step) {
	bFlipped = !bFlipped;
}

bool AABTrackPowersnapHologram::IsValidHitResult(const FHitResult& hitResult) const {
	return Cast<AFGBuildableRailroadTrack>(hitResult.GetActor()) != nullptr;
}

bool AABTrackPowersnapHologram::TrySnapToActor(const FHitResult& hitResult) {
	mSnappedTrack = Cast<AFGBuildableRailroadTrack>(hitResult.GetActor());

	USplineComponent* splineRef = mSnappedTrack->GetSplineComponent();
	FTransform close = splineRef->FindTransformClosestToWorldLocation(hitResult.Location, ESplineCoordinateSpace::World, true);

	SetActorTransform(close);
	if (bFlipped) { AddActorLocalRotation(FRotator(0, 180, 0)); }

	return true;
}

void AABTrackPowersnapHologram::ConfigureActor(class AFGBuildable* inBuildable) const {
	AABBuildableRailPower* PowerBox = Cast<AABBuildableRailPower>(inBuildable);
	if(PowerBox != nullptr) {
		PowerBox->mSnappedTrack = mSnappedTrack;
	}
}
