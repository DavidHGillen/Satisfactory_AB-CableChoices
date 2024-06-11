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
		FTransform worldToActor = actorToWorld.Inverse();
		FVector localHitPosition = worldToActor.TransformPosition(hitResult.ImpactPoint);
		FVector localHitNormal = worldToActor.TransformVector(hitResult.ImpactNormal);

		FVector outLocation = FVector(0.0f, 0.0f, FMath::GridSnap(FMath::Clamp(localHitPosition.Z, ruleset.minDistance, ruleset.maxDistance), mGridSnapSize));
		/////////////////////////////////////
		SetActorLocationAndRotation(actorToWorld.TransformPosition(outLocation), actorToWorld.TransformRotation(FQuat::Identity));
		AddActorLocalRotation(FRotator(90.0f, 0.0f, GetScrollRotateValue()));
		/////////////////////////////////////
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
		SetActorLocationAndRotation(actorToWorld.TransformPosition(outLocation), actorToWorld.TransformRotation(outRotation.Quaternion()));
		AddActorLocalOffset(FVector(0.0f, 0.0f, hitBeam->GetSize() * 0.5f));
		AddActorLocalRotation(FRotator(0.0f, GetScrollRotateValue() % 2 != 0 ? 0.0f : 180.0f, 0.0f));
		return;
	}

	// pillars
	AFGBuildablePillar* hitPillar = Cast<AFGBuildablePillar>(hitActor);
	if (hitPillar != NULL) {
		// pillars are guarenteed to be some rect with even dimensions
		outLocation = localHitPosition.GridSnap(mGridSnapSize);
		/////////////////////////////////////
		outRotation = FRotator(FQuat(localHitNormal, 0.0f)).GridSnap(FRotator(90.0f, 90.0f, 90.0f));
		/////////////////////////////////////
		SetActorLocationAndRotation(actorToWorld.TransformPosition(outLocation), actorToWorld.TransformRotation(outRotation.Quaternion()));
		AddActorLocalRotation(FRotator(90.0f, wallRot, 0.0f));
		return;
	}

	// wall placement
	AFGBuildableWall* hitWall = Cast<AFGBuildableWall>(hitActor);
	if (hitWall != NULL) {
		SnapToWall(hitWall, hitResult.ImpactNormal, hitResult.ImpactPoint, EAxis::Z, FVector::Zero(), wallRot, outLocation, outRotation);
		SetActorLocationAndRotation(outLocation, outRotation);
		AddActorLocalOffset(FVector(0.0f, 0.0f, wallOffset));
		return;
	}

	// foundations enable side snapping and handle underside snapping, also follow slopes
	AFGBuildableFoundation* hitFoundation = Cast<AFGBuildableFoundation>(hitActor);
	if (hitFoundation != NULL) {
		bool bOnTheUnderside = localHitNormal.Z < 0.0f;

		// foundation side helper
		if (FMath::Abs(localHitNormal.Z) <= 0.48f) {
			outLocation = hitResult.ImpactPoint;
			SnapToFoundationSide(hitFoundation, localHitNormal, EAxis::Z, outLocation, outRotation);
			SetActorLocationAndRotation(outLocation, outRotation);
			AddActorLocalRotation(FRotator(0.0f, wallRot, 0.0f));
			return;
		}

		// foundation top/bottom
		outLocation = localHitPosition.GridSnap(mGridSnapSize);
		float halfHeight = hitFoundation->mHeight * 0.5f;
		float groundOffset = 0.0f;
		float heightBound = 1.0f;

		if (bOnTheUnderside) {
			// if it's the bottom lets be upside down
			outRotation += FRotator(0.0f, 0.0f, 180.0f);
			heightBound = 0.0f;
		}

		if (FMath::Abs(localHitPosition.Z) < (halfHeight - 5.0f)) {
			// we're not on a flat top/bottom
			AFGBuildableRamp* hitRamp = Cast<AFGBuildableRamp>(hitActor);
			if (hitRamp != NULL) {
				// we're on a slope so let's handle that
				outRotation += FRotator(-hitRamp->CalculateRampAngle(), 0.0f, 0.0f);

				// so what does that mean for the z given slope
				heightBound = 1.0f - (outLocation.X / hitFoundation->mDepth + 0.5f); // 0 -> 1 height
				if (hitRamp->mIsDoubleRamp) {
					heightBound = heightBound * 0.5f + (bOnTheUnderside ? 0.0f : 0.5f);
				}
				if (hitRamp->mIsRoof) { groundOffset = wallOffset * (bOnTheUnderside ? -1.0f : 1.0f); }
			} else {
				// we're somewhere in the middle of something
				heightBound = FMath::GridSnap(localHitPosition.Z / hitFoundation->mHeight + 0.5f, mGridSnapSize / hitFoundation->mHeight);
			}
		}

		outLocation.Z = FMath::Lerp(-halfHeight, halfHeight, heightBound) + groundOffset;
		SetActorLocationAndRotation(actorToWorld.TransformPosition(outLocation), actorToWorld.TransformRotation(outRotation.Quaternion()));
		AddActorLocalRotation(FRotator(0.0f, wallRot, 0.0f));
		return;
	}

	// normal behaviour for remaining things
	Super::SetHologramLocationAndRotation(hitResult);
}
