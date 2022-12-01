#include "main.hpp"
#include "settings.hpp"

#include "questui/shared/BeatSaberUI.hpp"

#include "HMUI/Touchable.hpp"

void SettingsDidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {

    if(!firstActivation)
        return;
    
    self->get_gameObject()->AddComponent<HMUI::Touchable*>();
    auto vertical = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(self);
    vertical->set_childControlHeight(false);
    vertical->set_childForceExpandHeight(false);
    vertical->set_spacing(1);

    AddConfigValueToggle(vertical, getConfig().ShowWarning);
    AddConfigValueToggle(vertical, getConfig().OverrideLength);
    AddConfigValueIncrementFloat(vertical, getConfig().TransitionLength, 1, 0.1, 0, 2);
}
