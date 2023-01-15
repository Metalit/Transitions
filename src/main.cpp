#include "main.hpp"
#include "settings.hpp"

#include "GlobalNamespace/DefaultScenesTransitionsFromInit.hpp"
#include "GlobalNamespace/GameScenesManager.hpp"

#include "questui/shared/QuestUI.hpp"

using namespace GlobalNamespace;

static ModInfo modInfo;

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

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getConfig().Init(modInfo);

    LOG_INFO("Completed setup!");
}

extern "C" void load() {
    il2cpp_functions::Init();

    QuestUI::Register::RegisterModSettingsViewController(modInfo, SettingsDidActivate);

    LOG_INFO("Installing hooks...");
    INSTALL_HOOK(getLogger(), InitSceneTransitions);
    INSTALL_HOOK(getLogger(), PushSceneTransition);
    INSTALL_HOOK(getLogger(), PopSceneTransition);
    INSTALL_HOOK(getLogger(), ReplaceSceneTransition);
    LOG_INFO("Installed all hooks!");
}