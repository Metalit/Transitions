#include "main.hpp"

#include "GlobalNamespace/GameScenesManager.hpp"
#include "GlobalNamespace/HealthWarningFlowCoordinator.hpp"
#include "GlobalNamespace/InitialDestinationResolver.hpp"
#include "System/Threading/Tasks/Task.hpp"
#include "bsml/shared/BSML.hpp"
#include "logging.hpp"
#include "settings.hpp"

using namespace GlobalNamespace;


MAKE_HOOK_MATCH(
    PresentHealthWarningAsync,
    &InitialDestinationResolver::PresentHealthWarningAsync,
    System::Threading::Tasks::Task*,
    InitialDestinationResolver* self
) {
    if (!getConfig().ShowWarning.GetValue())
        return System::Threading::Tasks::Task::get_CompletedTask();
    return PresentHealthWarningAsync(self);
}

MAKE_HOOK_MATCH(
    PushSceneTransition,
    &GameScenesManager::PushScenes,
    void,
    GameScenesManager* self,
    ScenesTransitionSetupData* scenesTransitionSetupData,
    float minDuration,
    System::Action* afterMinDurationCallback,
    System::Action_1<Zenject::DiContainer*>* finishCallback
) {
    if (getConfig().OverrideLength.GetValue())
        minDuration = getConfig().TransitionLength.GetValue();

    PushSceneTransition(self, scenesTransitionSetupData, minDuration, afterMinDurationCallback, finishCallback);
}

MAKE_HOOK_MATCH(
    PopSceneTransition,
    &GameScenesManager::PopScenes,
    void,
    GameScenesManager* self,
    float minDuration,
    System::Action* afterMinDurationCallback,
    System::Action_1<Zenject::DiContainer*>* finishCallback
) {
    if (getConfig().OverrideLength.GetValue())
        minDuration = getConfig().TransitionLength.GetValue();

    PopSceneTransition(self, minDuration, afterMinDurationCallback, finishCallback);
}

MAKE_HOOK_MATCH(
    ReplaceSceneTransition,
    &GameScenesManager::ReplaceScenes,
    void,
    GameScenesManager* self,
    ScenesTransitionSetupData* scenesTransitionSetupData,
    ArrayW<System::Collections::IEnumerator*> beforeNewScenesActivateRoutines,
    float minDuration,
    System::Action* afterMinDurationCallback,
    System::Action_1<Zenject::DiContainer*>* finishCallback
) {
    if (getConfig().OverrideLength.GetValue())
        minDuration = getConfig().TransitionLength.GetValue();

    ReplaceSceneTransition(self, scenesTransitionSetupData, beforeNewScenesActivateRoutines, minDuration, afterMinDurationCallback, finishCallback);
}

EXPORT_FUNC void setup(CModInfo& info) {
    info.version = VERSION;
    info.id = MOD_ID;
    info.version_long = GIT_COMMIT;
    modInfo.assign(info);

    getConfig().Init(modInfo);

    LOG_INFO("Completed setup!");
}

EXPORT_FUNC void late_load() {

    BSML::Register::RegisterSettingsMenu("Transitions", SettingsDidActivate, true);

    LOG_INFO("Installing hooks...");
    INSTALL_HOOK(Logger, PresentHealthWarningAsync);
    INSTALL_HOOK(Logger, PushSceneTransition);
    INSTALL_HOOK(Logger, PopSceneTransition);
    INSTALL_HOOK(Logger, ReplaceSceneTransition);
}
