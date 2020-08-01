#include "../../headers/scene/scenemanager.h"
#include "../../headers/scene/scene.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager()
{
    // for (auto scn = scenes.begin(); scn != scenes.end(); ++scn)
    // {
    //     delete &scn;
    // }
}

std::shared_ptr<SceneManager> SceneManager::instance = 0;
bool SceneManager::initialized = false;

std::shared_ptr<SceneManager> SceneManager::GetInstance()
{
    if (!SceneManager::initialized)
    {
        SceneManager::initialized = true;
        SceneManager::instance = std::make_shared<SceneManager>();
    }

    return SceneManager::instance;
}

void SceneManager::Initialize()
{
    LOG("Setting up main scene.");

    this->dispatcher = std::make_shared<EventDispatcher>();

    this->current = std::make_shared<Scene>("default");

    this->dispatcher->dispatchEvent(EventType::SceneManagerInitialized, current);

    LOG("Main scene set up.");
}

void SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
    scenes->emplace(scene->id, scene);
}

void SceneManager::RemoveScene(std::shared_ptr<Scene> scene)
{
    // TODO: should it be destroyed
    scenes->erase(scene->id);
}

EMSCRIPTEN_BINDINGS(SceneManager)
{

    emscripten::class_<SceneManager>("SceneManager")
         .smart_ptr_constructor("SceneManager", &std::make_shared<SceneManager>)
        .class_function("GetInstance", &SceneManager::GetInstance, emscripten::allow_raw_pointers())
        .function("GetCurrentScene", &SceneManager::GetCurrentScene, emscripten::allow_raw_pointers());
}