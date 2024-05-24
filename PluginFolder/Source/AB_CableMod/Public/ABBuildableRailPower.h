#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "ABBuildableRailPower.generated.h"

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API AABBuildableRailPower : public AFGBuildable
{
	GENERATED_BODY()

public:
	AABBuildableRailPower();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	class UFGPowerConnectionComponent* GetThirdRail(AFGBuildableRailroadTrack* targetTrack) const;

public:
	UPROPERTY(SaveGame, Replicated, BlueprintReadWrite)
	AFGBuildableRailroadTrack* mSnappedTrack;
};
