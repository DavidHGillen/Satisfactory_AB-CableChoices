// Fill out your copyright notice in the Description page of Project Settings.



#include "ABPowerPoleCornerHologram.h"
#include "Math/UnrealMathUtility.h"
#include "FGConstructDisqualifier.h"

#include "FGBuildableBeam.h"
#include "FGBuildablePillar.h"
#include "Buildables/FGBuildablePowerPole.h"
#include "Buildables/FGBuildableRamp.h"
#include "Buildables/FGBuildableStair.h"
#include "Buildables/FGBuildableWall.h"
#include "Buildables/FGBuildableWalkway.h"

// FG Code
bool AABPowerPoleCornerHologram::IsValidHitResult(const FHitResult& hitResult) const {
	UE_LOG(LogTemp, Warning, TEXT("|_ _| IsValid?"));
	AActor* hitActor = hitResult.GetActor();
	if (hitActor == NULL) { return false; }

	bool valid = Super::IsValidHitResult(hitResult);

	return valid;
}

bool AABPowerPoleCornerHologram::TrySnapToActor(const FHitResult& hitResult) {
	UE_LOG(LogTemp, Warning, TEXT("|_ _| TrySnap!"));

	Super::TrySnapToActor(hitResult);

	// reset to avoid unexpected behaviours
	xExtent = yExtent = zExtent = 0;
	AActor* hitActor = hitResult.GetActor();

	//FRotator outRotation = FRotator::ZeroRotator;
	FVector outLocation = FVector::Zero();
	FTransform actorToWorld = hitActor->GetTransform();
	FTransform worldToActor = actorToWorld.Inverse();
	FVector localHitPosition = worldToActor.TransformPosition(hitResult.ImpactPoint);
	FVector localHitNormal = worldToActor.TransformVector(hitResult.ImpactNormal);


	AFGBuildableWall* hitWall = Cast<AFGBuildableWall>(hitActor);
	if (hitWall != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| WALL!"));
		SetActorLocationAndRotation(hitResult.Location, hitResult.Normal.Rotation());
		return true;
	}

	AFGBuildableFoundation* hitFoundation = Cast<AFGBuildableFoundation>(hitActor);
	if (hitFoundation != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| FOUNDER!"));
		SetActorLocationAndRotation(hitResult.Location, hitResult.Normal.Rotation());
		return true;
	}

	AFGBuildablePillar* hitPillar = Cast<AFGBuildablePillar>(hitActor);
	if (hitPillar != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| PILLS!"));
		SetActorLocationAndRotation(hitResult.Location, hitResult.Normal.Rotation());
		return true;
	}

	AFGBuildableBeam* hitBeam = Cast<AFGBuildableBeam>(hitActor);
	if (hitBeam != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("|_ _| BEAM!"));
		FBox clearanceSnap = hitBeam->GetCombinedClearanceBox();

		if (localHitPosition.Z > 0.0) {
			zExtent = 1;
			outLocation.Z = FMath::RoundFromZero(clearanceSnap.Max.Z);
		}
		else {
			zExtent = -1;
			outLocation.Z = FMath::RoundFromZero(clearanceSnap.Min.Z);
		}

		if (localHitPosition.Y > 0.0) {
			yExtent = 1;
			outLocation.Y = FMath::RoundFromZero(clearanceSnap.Max.Y);
		} else {
			yExtent = -1;
			outLocation.Y = FMath::RoundFromZero(clearanceSnap.Min.Y);
		}

		//xExtent = FMath::RoundFromZero(localHitNormal.Z);
		outLocation.X = FMath::GridSnap(localHitPosition.X, mGridSnapSize);

		UE_LOG(LogTemp, Warning, TEXT("|_ _| %i %i %i"), xExtent, yExtent, zExtent);

		FQuat outQuat;
		RotateToMatchExtents(outQuat);

		SetActorLocationAndRotation(
			actorToWorld.TransformPosition(outLocation),
			actorToWorld.TransformRotation(outQuat)
		);
		return true;
	}

	// no other responses found so lets do default
	UE_LOG(LogTemp, Warning, TEXT("|_ _| None of the above!"));
	SetActorLocationAndRotation(hitResult.Location, hitResult.Normal.Rotation());
	return true;
}

// custom
void AABPowerPoleCornerHologram::RotateToMatchExtents(FQuat& outQuat) {
	FVector direction = FVector(xExtent, yExtent, zExtent);
	direction.Normalize();
	outQuat = FQuat::MakeFromRotationVector(direction);
}
