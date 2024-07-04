#include "settings.hpp"

#include "HMUI/Touchable.hpp"
#include "bsml/shared/BSML-Lite.hpp"
#include "main.hpp"

void SettingsDidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    if (!firstActivation)
        return;

    self->gameObject->AddComponent<HMUI::Touchable*>();
    auto vertical = BSML::Lite::CreateVerticalLayoutGroup(self);
    vertical->childControlHeight = false;
    vertical->childForceExpandHeight = false;
    vertical->spacing = 1;
    vertical->rectTransform->anchoredPosition = {-15, -6};

    AddConfigValueToggle(vertical, getConfig().ShowWarning);
    AddConfigValueToggle(vertical, getConfig().OverrideLength);
    AddConfigValueIncrementFloat(vertical, getConfig().TransitionLength, 1, 0.1, 0, 2);

    for (int i = 0; i < vertical->transform->childCount; i++)
        vertical->transform->GetChild(i)->GetComponent<UnityEngine::UI::LayoutElement*>()->preferredWidth = 75;
}
