#pragma once

#include "CoreMinimal.h"
#include "FGSwatchGroup.h"
#include "FGSwatchGroup_ABPowerline.generated.h"

/**
 * 
 */
UCLASS()
class AB_CABLEMOD_API UFGSwatchGroup_ABPowerline : public UFGSwatchGroup
{
	GENERATED_BODY()
public:
	UFGSwatchGroup_ABPowerline()
	{
		mGroupName = FText::FromString("Powerline");
	}
};
