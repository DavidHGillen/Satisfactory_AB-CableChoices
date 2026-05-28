#pragma once

#include "CC_SwatchData.generated.h"

#define CC_StringPath "/AB_CableMod/Localization/CC_SharedStringTable.CC_SharedStringTable"

UCLASS()
class AB_CABLEMOD_API UFGSwatchGroup_Powerline_Std : public UFGSwatchGroup {
	GENERATED_BODY()
public:
	UFGSwatchGroup_Powerline_Std() {
		mGroupName = LOCTABLE(CC_StringPath, "SwatchGroup_PowerlineStd");
	}
};

UCLASS()
class AB_CABLEMOD_API UFGSwatchGroup_Powerline_AU : public UFGSwatchGroup {
	GENERATED_BODY()
public:
	UFGSwatchGroup_Powerline_AU() {
		mGroupName = LOCTABLE(CC_StringPath, "SwatchGroup_PowerlineAu");
	}
};

UCLASS()
class AB_CABLEMOD_API UFGSwatchGroup_Powerline_CU : public UFGSwatchGroup {
	GENERATED_BODY()
public:
	UFGSwatchGroup_Powerline_CU() {
		mGroupName = LOCTABLE(CC_StringPath, "SwatchGroup_PowerlineCu");
	}
};

UCLASS()
class AB_CABLEMOD_API UFGSwatchGroup_Powerline_SI : public UFGSwatchGroup {
	GENERATED_BODY()
public:
	UFGSwatchGroup_Powerline_SI() {
		mGroupName = LOCTABLE(CC_StringPath, "SwatchGroup_PowerlineSi");
	}
};