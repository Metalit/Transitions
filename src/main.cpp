#include "main.hpp"
#include "settings.hpp"

#include "GlobalNamespace/DefaultScenesTransitionsFromInit.hpp"
#include "GlobalNamespace/GameScenesManager.hpp"
#include "bsml/shared/BSML.hpp"


using namespace GlobalNamespace;

modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_MATCH(InitSceneTransitions, &DefaultScenesTransitionsFromInit::TransitionToNextScene,
        void, DefaultScenesTransitionsFromInit* self, bool goStraightToMenu, bool goStraightToEditor, bool goToRecordingToolScene) {

    if(!getConfig().ShowWarning.GetValue())
        goStraightToMenu = true;

    InitSceneTransitions(self, goStraightToMenu, goStraightToEditor, goToRecordingToolScene);
}

MAKE_HOOK_MATCH(PushSceneTransition, &GameScenesManager::PushScenes,
        void, GameScenesManager* self, ScenesTransitionSetupDataSO* scenesTransitionSetupData, float minDuration, System::Action* afterMinDurationCallback, System::Action_1<Zenject::DiContainer*>* finishCallback) {

    if(getConfig().OverrideLength.GetValue())
        minDuration = getConfig().TransitionLength.GetValue();

    PushSceneTransition(self, scenesTransitionSetupData, minDuration, afterMinDurationCallback, finishCallback);
}

MAKE_HOOK_MATCH(PopSceneTransition, &GameScenesManager::PopScenes,
        void, GameScenesManager* self, float minDuration, System::Action* afterMinDurationCallback, System::Action_1<Zenject::DiContainer*>* finishCallback) {

    if(getConfig().OverrideLength.GetValue())
        minDuration = getConfig().TransitionLength.GetValue();

    PopSceneTransition(self, minDuration, afterMinDurationCallback, finishCallback);
}

MAKE_HOOK_MATCH(ReplaceSceneTransition, &GameScenesManager::ReplaceScenes,
        void, GameScenesManager* self, ScenesTransitionSetupDataSO* scenesTransitionSetupData, ArrayW<System::Collections::IEnumerator*> beforeNewScenesActivateRoutines, float minDuration, System::Action* afterMinDurationCallback, System::Action_1<Zenject::DiContainer*>* finishCallback) {

    if(getConfig().OverrideLength.GetValue())
        minDuration = getConfig().TransitionLength.GetValue();

    ReplaceSceneTransition(self, scenesTransitionSetupData, beforeNewScenesActivateRoutines, minDuration, afterMinDurationCallback, finishCallback);
}

extern "C" __attribute__((visibility("default"))) void setup(CModInfo* info) {
    info->version = VERSION;
    info->id = MOD_ID;
    info->version_long = 0;
    modInfo.assign(*info);

    getConfig().Init(modInfo);

    LOG_INFO("Completed setup!");
}

extern "C" __attribute__((visibility("default"))) void late_load() {
    il2cpp_functions::Init();

    BSML::Register::RegisterSettingsMenu("Transitions", SettingsDidActivate, true);

    LOG_INFO("Installing hooks...");
    INSTALL_HOOK(getLogger(), InitSceneTransitions);
    INSTALL_HOOK(getLogger(), PushSceneTransition);
    INSTALL_HOOK(getLogger(), PopSceneTransition);
    INSTALL_HOOK(getLogger(), ReplaceSceneTransition);
    LOG_INFO("Installed all hooks!");
}