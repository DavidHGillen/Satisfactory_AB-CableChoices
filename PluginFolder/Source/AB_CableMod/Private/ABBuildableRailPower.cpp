#include "ABBuildableRailPower.h"
#include "Net/UnrealNetwork.h"

AABBuildableRailPower::AABBuildableRailPower() {
	mSnappedTrack = nullptr;
}

void AABBuildableRailPower::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AABBuildableRailPower, mSnappedTrack);
}

UFGPowerConnectionComponent* AABBuildableRailPower::GetThirdRail(AFGBuildableRailroadTrack* targetTrack) const {
	if (targetTrack != nullptr && GetLocalRole() == ENetRole::ROLE_Authority) {
		return targetTrack->GetThirdRail();
	}
	return nullptr;
}
