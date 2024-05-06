#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HUDInterface.generated.h"

// This class does not need to be modified.

UINTERFACE(MinimalAPI)
class UHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class IHUDInterface
{
	GENERATED_BODY()

public:
	virtual void ShowHUD() = 0;
	virtual void HideHUD() = 0;

	virtual void ShowCrosshair() = 0;
	virtual void HideCrosshair() = 0;
};
