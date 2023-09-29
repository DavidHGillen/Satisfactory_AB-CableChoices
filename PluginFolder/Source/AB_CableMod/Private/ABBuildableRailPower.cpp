#include "ABBuildableRailPower.h"

AABBuildableRailPower::AABBuildableRailPower() {
	mSnappedTrack = nullptr;
}

void AABBuildableRailPower::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AABBuildableRailPower, mSnappedTrack);
}

UFGPowerConnectionComponent* AABBuildableRailPower::GetThirdRail() const {
	if (mSnappedTrack != nullptr && GetLocalRole() == ENetRole::ROLE_Authority) {
		return mSnappedTrack->GetThirdRail();
	}
	return nullptr;
}
