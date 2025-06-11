#include "main.hpp"

#include "GlobalNamespace/DefaultScenesTransitionsFromInit.hpp"
#include "GlobalNamespace/GameScenesManager.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "bsml/shared/BSML.hpp"
#include "main.hpp"
#include "scotland2/shared/modloader.h"
#include "settings.hpp"

using namespace GlobalNamespace;

modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

MAKE_HOOK_MATCH(
    InitSceneTransitions,
    &DefaultScenesTransitionsFromInit::TransitionToNextScene,
    void,
    DefaultScenesTransitionsFromInit* self,
    bool goStraightToMenu,
    bool goStraightToEditor,
    bool goToRecordingToolScene,
    System::Action* onFinishShaderWarmup
) {
    if (!getConfig().ShowWarning.GetValue())
        goStraightToMenu = true;
    InitSceneTransitions(self, goStraightToMenu, goStraightToEditor, goToRecordingToolScene, onFinishShaderWarmup);
}

MAKE_HOOK_MATCH(
    PushSceneTransition,
    &GameScenesManager::PushScenes,
    void,
    GameScenesManager* self,
    ScenesTransitionSetupDataSO* scenesTransitionSetupData,
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
    ScenesTransitionSetupDataSO* scenesTransitionSetupData,
    ArrayW<System::Collections::IEnumerator*> beforeNewScenesActivateRoutines,
    float minDuration,
    System::Action* afterMinDurationCallback,
    System::Action_1<Zenject::DiContainer*>* finishCallback
) {
    if (getConfig().OverrideLength.GetValue())
        minDuration = getConfig().TransitionLength.GetValue();

    ReplaceSceneTransition(self, scenesTransitionSetupData, beforeNewScenesActivateRoutines, minDuration, afterMinDurationCallback, finishCallback);
}

extern "C" void setup(CModInfo* info) {
    info->version = VERSION;
    info->id = MOD_ID;
    info->version_long = 0;
    modInfo.assign(*info);

    Paper::Logger::RegisterFileContextId(MOD_ID);

    getConfig().Init(modInfo);

    LOG_INFO("Completed setup!");
}

extern "C" void late_load() {
    il2cpp_functions::Init();

    BSML::Register::RegisterSettingsMenu("Transitions", SettingsDidActivate, true);

    LOG_INFO("Installing hooks...");
    INSTALL_HOOK(logger, InitSceneTransitions);
    INSTALL_HOOK(logger, PushSceneTransition);
    INSTALL_HOOK(logger, PopSceneTransition);
    INSTALL_HOOK(logger, ReplaceSceneTransition);
    LOG_INFO("Installed all hooks!");
}
