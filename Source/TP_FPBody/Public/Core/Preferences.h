#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/PlayerController.h"
#include "Preferences.generated.h"

USTRUCT(BlueprintType)
struct FPreferences
{
    GENERATED_BODY()

    // Graphics settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graphics")
    float FOV = 90.0f; // Player field of view

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graphics")
    int32 ScreenResolutionX = 1920; // Screen horizontal resolution

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graphics")
    int32 ScreenResolutionY = 1080; // Screen vertical resolution

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graphics")
    bool bFullScreen = true; // Fullscreen mode

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Graphics")
    bool bVSync = false; // Vertical synchronization

    // Audio settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
    float MasterVolume = 1.0f; // Master volume level

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
    float EffectsVolume = 1.0f; // Sound effects volume

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
    float MusicVolume = 0.5f; // Music volume

    // Control settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controls")
    float MouseSensitivityX = 1.0f; // Mouse horizontal sensitivity

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controls")
    float MouseSensitivityY = 1.0f; // Mouse vertical sensitivity

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controls")
    bool bInvertYAxis = false; // Invert Y-axis

    // Gameplay settings
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
    bool bAutoReload = true; // Automatic weapon reload

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
    bool bShowHUD = true; // Display heads-up display

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Gameplay")
    bool bEnableBlood = true; // Enable blood effects
};
