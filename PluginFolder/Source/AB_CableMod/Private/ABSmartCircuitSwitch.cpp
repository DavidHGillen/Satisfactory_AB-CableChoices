#include "ABSmartCircuitSwitch.h"

AABSmartCircuitSwitch::AABSmartCircuitSwitch() {}

void AABSmartCircuitSwitch::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AABSmartCircuitSwitch, fWaitLength);
	DOREPLIFETIME(AABSmartCircuitSwitch, fGameTime_Trigger);
	DOREPLIFETIME(AABSmartCircuitSwitch, iCustomState);
}

// custom
float AABSmartCircuitSwitch::GetClampedProgressAtTime(float fGameTime) {
	if (fGameTime <= 0) { fGameTime = GetWorld()->GetTimeSeconds(); }

	if (!IsBridgeConnected()) { return 0.0f; }

	return FMath::Clamp((fGameTime_Trigger - fGameTime) / fWaitLength, 1.0f, 0.0f);
}

void AABSmartCircuitSwitch::ResetTriggerMoment(bool bResetProgress, float fNewWaitLength) {
	float fGameTime = GetWorld()->GetTimeSeconds();
	float progress = bResetProgress ? 0.0f : GetClampedProgressAtTime(fGameTime);

	if (fNewWaitLength >= 0) {
		fWaitLength = fNewWaitLength;
	}

	fGameTime_Trigger = fGameTime + (1.0f - progress) * fWaitLength;
}

// base
void AABSmartCircuitSwitch::PreSave(FObjectPreSaveContext SaveContext) {
	if (iCustomState == 2) {
		fProgressAtSave = GetClampedProgressAtTime();
	}

	Super::PreSave(SaveContext);
};

void AABSmartCircuitSwitch::PostLoad() {
	Super::PostLoad();

	if (iCustomState == 2) {
		fGameTime_Trigger = GetWorld()->GetTimeSeconds() + (fProgressAtSave * fWaitLength);
	}
};