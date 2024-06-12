// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPowerSwitchHologramWallmount.h"
#include "Math/UnrealMathUtility.h"
#include "FGConstructDisqualifier.h"

#include "FGBuildableBeam.h"
#include "FGBuildablePillar.h"
#include "Buildables/FGBuildableWall.h"
#include "Buildables/FGBuildableRamp.h"
#include "Buildables/FGBuildableRailroadTrack.h"

AABPowerSwitchHologramWallmount::AABPowerSwitchHologramWallmount() {
	mSnappedBuilding = NULL;
}

bool AABPowerSwitchHologramWallmount::IsValidHitResult(const FHitResult& hitResult) const {
	AActor* hitActor = hitResult.GetActor();
	if (hitActor == NULL) { return false; }

	if (Cast<AFGBuildableRailroadTrack>(hitActor) != NULL) {
		return false;
	}

	if (Cast<AFGBuildableWall>(hitActor) != NULL) {
		return true;
	}

	AFGBuildablePillar* hitPillar = Cast<AFGBuildablePillar>(hitActor);
	if (hitPillar != NULL && hitPillar->IsSupport()) {
		return false;
	}

	for (int i = 0, l = poleSnapRules.Num(); i < l; i++) {
		TSubclassOf<AFGBuildable> classref = poleSnapRules[i].buildableClass->GetDefaultObject()->GetClass();
		if (classref != NULL && hitActor->GetClass()->IsChildOf(classref)) {
			return true;
		}
	}

	return Super::IsValidHitResult(hitResult);
}

bool AABPowerSwitchHologramWallmount::CanNudgeHologram() const {
	return mSnappedBuilding == NULL;
}

bool AABPowerSwitchHologramWallmount::TrySnapToActor(const FHitResult& hitResult) {
	AActor* hitActor = hitResult.GetActor();
	mSnappedBuilding = NULL;

	// special explict placements
	for (int i = 0, l = poleSnapRules.Num(); i < l; i++) {
		FPoleSnapData ruleset = poleSnapRules[i];
		TSubclassOf<AFGBuildable> classref = ruleset.buildableClass->GetDefaultObject()->GetClass();

		if (!hitActor->GetClass()->IsChildOf(classref)) { continue; }
		mSnappedBuilding = Cast<AFGBuildable>(hitActor);

		FTransform actorToWorld = hitActor->GetTransform();
		FVector relativeHitPosition = actorToWorld.Inverse().TransformPosition(hitResult.ImpactPoint) - ruleset.offset;

		float localAproachRad = FMath::GridSnap(FMath::Atan2(relativeHitPosition.Y, relativeHitPosition.X), FMath::DegreesToRadians(15.0f));
		FVector outLocation = FVector(0.0f, 0.0f, FMath::GridSnap(FMath::Clamp(relativeHitPosition.Z, ruleset.minDistance, ruleset.maxDistance), mGridSnapSize));
		FRotator outRotation = FRotator(-90.0f, 0.0f, FMath::RadiansToDegrees(localAproachRad));
		SetActorLocationAndRotation(
			actorToWorld.TransformPosition(outLocation + ruleset.offset),
			actorToWorld.TransformRotation(outRotation.Quaternion())
		);
		AddActorLocalRotation(FRotator(0.0f, GetScrollRotateValue() % 2 ? 180.0f : 0.0f, 0.0f));
		AddActorLocalOffset(FVector(0.0f, 0.0f, ruleset.radius));
		return true;
	}

	return false;
}

void AABPowerSwitchHologramWallmount::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	FRotator outRotation = FRotator::ZeroRotator;
	FVector outLocation = FVector::Zero();
	AActor* hitActor = hitResult.GetActor();

	FTransform actorToWorld = hitActor->GetTransform();
	FTransform worldToActor = actorToWorld.Inverse();
	FVector localHitPosition = worldToActor.TransformPosition(hitResult.ImpactPoint);
	FVector localHitNormal = worldToActor.TransformVector(hitResult.ImpactNormal);
	float wallRot = allowSpinOnWall ? GetScrollRotateValue() : 0.0f;

	// beams
	AFGBuildableBeam* hitBeam = Cast<AFGBuildableBeam>(hitActor);
	if (hitBeam != NULL) {
		// incase somone bevels the edges of the beam or something, snap to cardinal directions and local units
		float facing = FMath::Abs(localHitNormal.Y) > FMath::Abs(localHitNormal.Z) ? (localHitNormal.Y > 0.0f ? 90.0f: 270.0f) : (localHitNormal.Z > 0.0f ? 0.0f: 180.0f);
		outLocation = FVector(FMath::GridSnap(localHitPosition.X, mGridSnapSize), 0.0f, 0.0f);
		outRotation = FRotator(0.0f, 0.0f, facing);

		// place us where we should be in the world, and now we know we're where we should be facing the way we should be, move outside the beam
		SetActorLocationAndRotation(
			actorToWorld.TransformPosition(outLocation),
			actorToWorld.TransformRotation(outRotation.Quaternion())
		);
		AddActorLocalOffset(FVector(0.0f, 0.0f, hitBeam->GetSize() * 0.5f));
		AddActorLocalRotation(FRotator(0.0f, GetScrollRotateValue() % 2 != 0 ? 0.0f : 180.0f, 0.0f));
		return;
	}

	// pillars
	AFGBuildablePillar* hitPillar = Cast<AFGBuildablePillar>(hitActor);
	if (hitPillar != NULL) {
		// pillars are guarenteed to be some rect with even dimensions
		outLocation = localHitPosition.GridSnap(mGridSnapSize);
		outRotation = localHitNormal.GridSnap(1.0f).Rotation();
		SetActorLocationAndRotation(
			actorToWorld.TransformPosition(outLocation),
			actorToWorld.TransformRotation(outRotation.Quaternion())
		);
		AddActorLocalRotation(FRotator(-90.0f, 0.0f, 0.0f));
		AddActorLocalRotation(FRotator(0.0f, wallRot, 0.0f));
		return;
	}

	// wall placement
	AFGBuildableWall* hitWall = Cast<AFGBuildableWall>(hitActor);
	if (hitWall != NULL) {
		SnapToWall(hitWall, hitResult.ImpactNormal, hitResult.ImpactPoint, EAxis::Z, FVector::Zero(), wallRot, outLocation, outRotation);
		SetActorLocationAndRotation(
			outLocation,
			outRotation
		);
		AddActorLocalOffset(FVector(0.0f, 0.0f, wallOffset));
		return;
	}

	// foundations enable side snapping and handle underside snapping, also follow slopes
	AFGBuildableFoundation* hitFoundation = Cast<AFGBuildableFoundation>(hitActor);
	if (hitFoundation != NULL) {
		FVector absLocalNormal = localHitNormal.GetAbs();
		bool nonCardinal = absLocalNormal.X < 0.998f && absLocalNormal.Y < 0.998f && absLocalNormal.Z < 0.998f;
		bool onTheUnderside = localHitNormal.Z < 0.0f;

		UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ lhn %f, %f, %f"), localHitNormal.X, localHitNormal.Y, localHitNormal.Z);
		UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ ahn %f, %f, %f"), absLocalNormal.X, absLocalNormal.Y, absLocalNormal.Z);
		
		if (nonCardinal) { UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ NON POPE ")); }
		else {             UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ POPE ")); }

		if (onTheUnderside) { UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ Swing Low ")); }
		else {                UE_LOG(LogTemp, Warning, TEXT("~~~ ~~~ Sweet Charriot ")); }

		AFGBuildableRamp* hitRamp = Cast<AFGBuildableRamp>(hitActor);
		if (hitRamp != NULL && nonCardinal) {
			// ramp's ramped surface enjoy special behaviours not of the utility
			float slopeHigh = hitRamp->mElevation * 0.5f;
			float slopeLow = hitRamp->mElevation * -0.5f;

			if (hitRamp->mIsDoubleRamp && onTheUnderside) {
				// double ramps are basically single ramps with an offset underneath ramp
				slopeLow -= hitRamp->mHeight;
				slopeHigh -= hitRamp->mHeight;
			} else if (hitRamp->mIsRoof) {
				// roofs are thick and about the same as walls so lets reuse that offset
				slopeLow += onTheUnderside ? -wallOffset : wallOffset;
				slopeHigh += onTheUnderside ? -wallOffset : wallOffset;
			}

			outLocation = localHitPosition.GridSnap(mGridSnapSize);
			outRotation = FRotator(-hitRamp->CalculateRampAngle(), 0.0f, onTheUnderside ? 180.0f : 0.0f);
			outLocation.Z = FMath::Lerp(slopeHigh, slopeLow, outLocation.X / hitRamp->mDepth + 0.5f);

			SetActorLocationAndRotation(
				actorToWorld.TransformPosition(outLocation),
				actorToWorld.TransformRotation(outRotation.Quaternion())
			);
		} else {
			// the default utility is fine here
			outLocation = hitResult.ImpactPoint;
			SnapToFoundationSide(hitFoundation, localHitNormal, EAxis::Z, outLocation, outRotation);
			SetActorLocationAndRotation(
				outLocation,
				outRotation
			);
		}

		AddActorLocalRotation(FRotator(0.0f, wallRot, 0.0f));
		return;
	}

	// normal behaviour for remaining things
	Super::SetHologramLocationAndRotation(hitResult);
}
