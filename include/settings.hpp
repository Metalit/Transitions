#pragma once

#include "config-utils/shared/config-utils.hpp"
#include "HMUI/ViewController.hpp"

DECLARE_CONFIG(Config,
    CONFIG_VALUE(ShowWarning, bool, "Show Warning", false, "Shows the health warning when the game launches");
    CONFIG_VALUE(OverrideLength, bool, "Override Scene Transitions", true, "Forces all scene transitions to be a specific duration");
    CONFIG_VALUE(TransitionLength, float, "Scene Transitions Length", 0.2, "The duration to force for all transitions");
)

void SettingsDidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);
