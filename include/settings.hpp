#pragma once

#define HAS_CODEGEN
#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(Config,
    CONFIG_VALUE(ShowWarning, bool, "Show Warning", false, "Whether to show the health warning when the game launches");
    CONFIG_VALUE(OverrideLength, bool, "Override Scene Transitions", true, "Whether to force all scene transitions to be a specific duration");
    CONFIG_VALUE(TransitionLength, float, "Scene Transitions Length", 0.2, "The duration to force for all transitions");

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(ShowWarning);
        CONFIG_INIT_VALUE(OverrideLength);
        CONFIG_INIT_VALUE(TransitionLength);
    )
)

#include "HMUI/ViewController.hpp"

void SettingsDidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);