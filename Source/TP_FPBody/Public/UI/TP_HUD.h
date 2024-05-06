#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/HUDInterface.h"
#include "TP_HUD.generated.h"

UCLASS()
class TP_FPBODY_API UTP_HUD : public UUserWidget, public IHUDInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void ShowHUD();
	virtual void ShowHUD_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void HideHUD();
	virtual void HideHUD_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void ShowCrosshair();
	virtual void ShowCrosshair_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HUD")
	void HideCrosshair();
	virtual void HideCrosshair_Implementation();
};
