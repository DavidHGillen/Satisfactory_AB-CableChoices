// Fill out your copyright notice in the Description page of Project Settings.



#include "ABPowerPoleCornerHologram.h"
#include "Math/UnrealMathUtility.h"
#include "FGConstructDisqualifier.h"

#include "FGBuildableBeam.h"
#include "FGBuildablePillar.h"
#include "Buildables/FGBuildableBlueprintDesigner.h"
#include "Buildables/FGBuildableRamp.h"
#include "Buildables/FGBuildableWall.h"
#include "Buildables/FGBuildableCornerWall.h"
#include "Buildables/FGBuildableWalkway.h"

// FG Code
void AABPowerPoleCornerHologram::ScrollRotate(int32 delta, int32 step) {
	if (Cast<AFGBuildableWall>(mSnappedBuilding) != NULL) {
		bNarrowFlip = !bNarrowFlip;
	} else {
		Super::ScrollRotate(delta, step);
	}
}

bool AABPowerPoleCornerHologram::IsValidHitResult(const FHitResult& hitResult) const {
	TObjectPtr<AActor> hitActor = hitResult.GetActor();

	// ficsit objects only
	TObjectPtr<AFGBuildable> hitBuildable = Cast<AFGBuildable>(hitActor);
	if (hitBuildable == NULL) { return false; }

	// gets weird results lets just skip past that bit
	TObjectPtr<AFGBuildableBlueprintDesigner> hitDesigner = Cast<AFGBuildableBlueprintDesigner>(hitActor);
	if (hitDesigner != NULL) { return false; }

	// allow the weird diagonal pieces
	TObjectPtr<AFGBuildableCornerWall> hitCornerWall = Cast<AFGBuildableCornerWall>(hitActor);
	if (hitCornerWall != NULL) { return true; }

	// allow the normal walls
	TObjectPtr<AFGBuildableWall> hitWall = Cast<AFGBuildableWall>(hitActor);
	if (hitWall != NULL) { return true; }

	//business as usual
	return Super::IsValidHitResult(hitResult);
}

bool AABPowerPoleCornerHologram::TrySnapToActor(const FHitResult& hitResult) {
	UE_LOG(LogTemp, Warning, TEXT("|_ _| TrySnap!"));

	// reset to avoid unexpected behaviours
	xExtent = yExtent = zExtent = 0;
	TObjectPtr<AActor> hitActor = hitResult.GetActor();

	// shared transformation data
	FQuat outQuat;
	FVector outLocation = FVector::Zero();
	FTransform actorToWorld = hitActor->GetTransform();
	FTransform worldToActor = actorToWorld.Inverse();
	FVector localHitPosition = worldToActor.TransformPosition(hitResult.ImpactPoint);
	FVector localHitNormal = worldToActor.TransformVector(hitResult.ImpactNormal);

	// pillars
	TObjectPtr<AFGBuildablePillar> hitPillar = Cast<AFGBuildablePillar>(hitActor);
	if (hitPillar != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| PILLS!"));

		FVector halfBound = hitPillar->GetSize() / 2;

		if (localHitPosition.Z < (-halfBound.Z) + mGridSnapSize/2 || localHitPosition.Z > halfBound.Z - mGridSnapSize/2) {
			if (abs(localHitPosition.X) > abs(localHitPosition.Y)) {
				ApplyXExtent(0.0f, localHitPosition.X, -halfBound.X, halfBound.X, outLocation);
				outLocation.Y = FMath::GridSnap(localHitPosition.Y, mGridSnapSize);
			} else {
				outLocation.X = FMath::GridSnap(localHitPosition.X, mGridSnapSize);
				ApplyYExtent(0.0f, localHitPosition.Y, -halfBound.Y, halfBound.Y, outLocation);
			}
			ApplyZExtent(0.0f, localHitPosition.Z, -halfBound.Z, halfBound.Z, outLocation);
		} else {
			ApplyXExtent(0.0f, localHitPosition.X, -halfBound.X, halfBound.X, outLocation);
			ApplyYExtent(0.0f, localHitPosition.Y, -halfBound.Y, halfBound.Y, outLocation);
			outLocation.Z = FMath::GridSnap(localHitPosition.Z, mGridSnapSize);
		}

		RotateToMatchExtents(outQuat);
		SetActorLocationAndRotation(
			actorToWorld.TransformPosition(outLocation),
			actorToWorld.TransformRotation(outQuat)
		);

		return true;
	}

	// beams
	TObjectPtr<AFGBuildableBeam> hitBeam = Cast<AFGBuildableBeam>(hitActor);
	if (hitBeam != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| BEAM!"));
		FBox clearanceSnap = hitBeam->GetCombinedClearanceBox();

		float beamMin = 0.0f;
		float beamMax = hitBeam->GetLength();

		if(localHitPosition.X < beamMin + mGridSnapSize/2 || localHitPosition.X > beamMax - mGridSnapSize/2) {
			ApplyXExtent(mGridSnapSize/2, localHitPosition.X, beamMin, beamMax, outLocation);

			if (abs(localHitPosition.Y) > abs(localHitPosition.Z)) {
				ApplyYExtent(0.0f, localHitPosition.Y, clearanceSnap.Min.Y, clearanceSnap.Max.Y, outLocation);
				outLocation.Z = 0;
			} else {
				outLocation.Y = 0;
				ApplyZExtent(0.0f, localHitPosition.Z, clearanceSnap.Min.Z, clearanceSnap.Max.Z, outLocation);
			}
		} else {
			outLocation.X = FMath::GridSnap(localHitPosition.X, mGridSnapSize);
			ApplyYExtent(0.0f, localHitPosition.Y, clearanceSnap.Min.Y, clearanceSnap.Max.Y, outLocation);
			ApplyZExtent(0.0f, localHitPosition.Z, clearanceSnap.Min.Z, clearanceSnap.Max.Z, outLocation);
		}

		RotateToMatchExtents(outQuat);
		SetActorLocationAndRotation(
			actorToWorld.TransformPosition(outLocation),
			actorToWorld.TransformRotation(outQuat)
		);
		return true;
	}

	// foundation & ramp
	TObjectPtr<AFGBuildableFoundation> hitFoundation = Cast<AFGBuildableFoundation>(hitActor);
	if (hitFoundation != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| FOUNDER!"));
		SetActorLocationAndRotation(hitResult.Location, hitResult.Normal.Rotation());
		return true;
	}

	// wall & barricade
	TObjectPtr<AFGBuildableWall> hitWall = Cast<AFGBuildableWall>(hitActor);
	if (hitWall != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| WALL!"));
		SetActorLocationAndRotation(hitResult.Location, hitResult.Normal.Rotation());
		return true;
	}

	// weirdo sloped corners
	TObjectPtr<AFGBuildableCornerWall> hitCornerWall = Cast<AFGBuildableCornerWall>(hitActor);
	if (hitCornerWall == NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| CORNER WALL!"));

		SetActorLocationAndRotation(hitResult.Location, hitResult.Normal.Rotation());

		return true;
	}

	// lets act like default because there's nothing for us to do
	UE_LOG(LogTemp, Warning, TEXT("|_ _| None of the above!"));
	return Super::TrySnapToActor(hitResult);
}

// custom
void AABPowerPoleCornerHologram::RotateToMatchExtents(FQuat& outQuat) {
	FVector forwards = FVector(xExtent, yExtent, zExtent);

	// todo, ewww no this wont work for non cardinal setups
	if (forwards.Length() < 1.1f) {
		// flat surface, assume a wall with no x depth
		// todo, uhhhhh rooofs?!
		forwards.X = bNarrowFlip ? -1.0f : 1.0f;
	}
	
	FVector upwards = FVector(FVector(1.0f) - forwards.GetAbs());
	forwards.Normalize();
	upwards.Normalize();

	outQuat = FMatrix(forwards, upwards.Cross(forwards), upwards, FVector::ZeroVector).ToQuat();
}

void AABPowerPoleCornerHologram::ApplyXExtent(float border, float hitPos, float min, float max, FVector& outLocation) {
	if (hitPos > border) {
		xExtent = 1;
		outLocation.X = FMath::RoundFromZero(max);
	} else {
		xExtent = -1;
		outLocation.X = FMath::RoundFromZero(min);
	}
}

void AABPowerPoleCornerHologram::ApplyYExtent(float border, float hitPos, float min, float max, FVector& outLocation) {
	if (hitPos > border) {
		yExtent = 1;
		outLocation.Y = FMath::RoundFromZero(max);
	} else {
		yExtent = -1;
		outLocation.Y = FMath::RoundFromZero(min);
	}
}

void AABPowerPoleCornerHologram::ApplyZExtent(float border, float hitPos, float min, float max, FVector& outLocation) {
	if (hitPos > border) {
		zExtent = 1;
		outLocation.Z = FMath::RoundFromZero(max);
	} else {
		zExtent = -1;
		outLocation.Z = FMath::RoundFromZero(min);
	}
}
