#include "main.hpp"

#include "settings.hpp"
#include "beatsaber-hook/shared/hooking.hpp"
#include "bsml/shared/BSML.hpp"

#include "GlobalNamespace/GameScenesManager.hpp"
#include "GlobalNamespace/HealthWarningFlowCoordinator.hpp"
#include "GlobalNamespace/InitialDestinationResolver.hpp"
#include "System/Threading/Tasks/Task.hpp"

static modloader::ModInfo modInfo = {MOD_ID, VERSION, 0};

using namespace GlobalNamespace;

MAKE_HOOK_MATCH(
    InitialDestinationResolver_PresentHealthWarningAsync,
    &InitialDestinationResolver::PresentHealthWarningAsync,
    System::Threading::Tasks::Task*,
    InitialDestinationResolver* self
) {
    if (!getConfig().ShowWarning.GetValue())
        return System::Threading::Tasks::Task::get_CompletedTask();
    return InitialDestinationResolver_PresentHealthWarningAsync(self);
}

MAKE_HOOK_MATCH(
    GameScenesManager_PushScenes,
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

    GameScenesManager_PushScenes(self, scenesTransitionSetupData, minDuration, afterMinDurationCallback, finishCallback);
}

MAKE_HOOK_MATCH(
    GameScenesManager_PopScenes,
    &GameScenesManager::PopScenes,
    void,
    GameScenesManager* self,
    float minDuration,
    System::Action* afterMinDurationCallback,
    System::Action_1<Zenject::DiContainer*>* finishCallback
) {
    if (getConfig().OverrideLength.GetValue())
        minDuration = getConfig().TransitionLength.GetValue();

    GameScenesManager_PopScenes(self, minDuration, afterMinDurationCallback, finishCallback);
}

MAKE_HOOK_MATCH(
    GameScenesManager_ReplaceScenes,
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

    GameScenesManager_ReplaceScenes(
        self, scenesTransitionSetupData, beforeNewScenesActivateRoutines, minDuration, afterMinDurationCallback, finishCallback
    );
}

extern "C" __attribute__((visibility("default"))) void setup(CModInfo* info) {
    *info = modInfo.to_c();
    getConfig().Init(modInfo);

    logger.info("Completed setup!");
}

extern "C" __attribute__((visibility("default"))) void late_load() {
    BSML::Register::RegisterSettingsMenu("Transitions", SettingsDidActivate, true);

    logger.info("Installing hooks...");
    INSTALL_HOOK(logger, InitialDestinationResolver_PresentHealthWarningAsync);
    INSTALL_HOOK(logger, GameScenesManager_PushScenes);
    INSTALL_HOOK(logger, GameScenesManager_PopScenes);
    INSTALL_HOOK(logger, GameScenesManager_ReplaceScenes);
    logger.info("Installed all hooks!");
}
