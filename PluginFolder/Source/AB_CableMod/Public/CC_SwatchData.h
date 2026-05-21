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