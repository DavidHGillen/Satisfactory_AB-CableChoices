// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPowerSwitchHologramWallmount.h"
#include "Math/UnrealMathUtility.h"
#include "FGConstructDisqualifier.h"

#include "Buildables/FGBuildableWall.h"
#include "Buildables/FGBuildableRamp.h"
#include "Buildables/FGBuildableRailroadTrack.h"

bool AABPowerSwitchHologramWallmount::IsValidHitResult(const FHitResult& hitResult) const {
	if (Cast<AFGBuildableRailroadTrack>(hitResult.GetActor()) != NULL) {
		return false;
	}

	if (Cast<AFGBuildableWall>(hitResult.GetActor()) != NULL) {
		return true;
	}

	return Super::IsValidHitResult(hitResult);
}

void AABPowerSwitchHologramWallmount::SetHologramLocationAndRotation(const FHitResult& hitResult) {
	FRotator outRotation = FRotator::ZeroRotator;
	FVector outLocation = FVector::Zero();
	AActor* hitActor = hitResult.GetActor();
	float wallRot = allowSpinOnWall ? GetScrollRotateValue() : 0.0f;

	/*TODO:
		Beams: Lengthwise
		Pillars: Lengthwise
		Roofs: Underside point down
		Foundations: Side
		Catwalks: disallow
		Streetlights: Pole snapping
		Powerpole: Pole snapping
	*/

	// standard just doesn't attach to walls, so do it
	AFGBuildableWall* hitWall = Cast<AFGBuildableWall>(hitActor);
	if (snapToWalls && hitWall != NULL) {
		SnapToWall(hitWall, hitResult.ImpactNormal, hitResult.ImpactPoint, EAxis::Z, FVector::Zero(), wallRot, outLocation, outRotation);
		SetActorLocationAndRotation(outLocation, outRotation);
		return;
	}

	// enable side snapping and handle underside snapping
	AFGBuildableFoundation* hitFoundation = Cast<AFGBuildableFoundation>(hitActor);
	if (hitFoundation != NULL) {
		if(snapToFoundationSides && FMath::Abs(hitResult.ImpactNormal.Z) <= 0.75f) {
			SnapToFoundationSide(hitFoundation, hitResult.ImpactNormal, EAxis::Z, outLocation, outRotation);
			SetActorLocationAndRotation(outLocation, outRotation);
			//AddActorLocalRotation(FRotator(0.0f, wallRot, 0.0f));
			return;
		}

		Super::SetHologramLocationAndRotation(hitResult);
		if (hitResult.ImpactNormal.Z <= 0.0f) {
			AddActorLocalRotation(FRotator(180.0f, 0.0f, 0.0f));
		}
		return;
	}

	// no special cases so whatever vanilla wants
	Super::SetHologramLocationAndRotation(hitResult);
}
