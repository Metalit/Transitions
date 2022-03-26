#include "main.hpp"
#include "settings.hpp"

#include "questui/shared/BeatSaberUI.hpp"

#include "HMUI/Touchable.hpp"

using namespace QuestUI;
using namespace UnityEngine;
using namespace UnityEngine::UI;
using namespace HMUI;

DEFINE_CONFIG(Config);

void SettingsDidActivate(ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if(!firstActivation)
        return;
    
    self->get_gameObject()->AddComponent<Touchable*>();
    auto container = BeatSaberUI::CreateScrollableSettingsContainer(self)->get_transform();

    AddConfigValueToggle(container, getConfig().ShowWarning);
    AddConfigValueToggle(container, getConfig().OverrideLength);
    AddConfigValueIncrementFloat(container, getConfig().TransitionLength, 1, 0.1, 0, 2);
}
